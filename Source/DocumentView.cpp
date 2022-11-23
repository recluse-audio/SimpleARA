/*
  ==============================================================================

    DocumentView.cpp
    Created: 1 Nov 2022 12:50:54pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DocumentView.h"
#include "PluginEditor.h"

//==============================================================================
DocumentView::DocumentView(SimpleARAEditor& editor, juce::ARADocument& document, PlayHeadState& playHeadState)
: mEditor(editor),
  araDocument (document),
  overlay (playHeadState)
{
	addAndMakeVisible (tracksBackground);

	viewport.onVisibleAreaChanged = [this] (const auto& r)
	{
		viewportHeightOffset = r.getY();
		overlay.setHorizontalOffset (r.getX());
		resized();
	};

	addAndMakeVisible (viewport);

	overlay.setZoomLevel (zoomLevelPixelPerSecond);
	addAndMakeVisible (overlay);

	zoomControls.setZoomInCallback  ([this] { zoom (2.0); });
	zoomControls.setZoomOutCallback ([this] { zoom (0.5); });
	addAndMakeVisible (zoomControls);

	invalidateRegionSequenceViews();
	araDocument.addListener (this);
}

DocumentView::~DocumentView()
{
	araDocument.removeListener (this);

}


// ARADocument::Listener overrides
void DocumentView::didReorderRegionSequencesInDocument (juce::ARADocument*)
{
	invalidateRegionSequenceViews();
}

void DocumentView::didAddRegionSequenceToDocument (juce::ARADocument*, juce::ARARegionSequence*)
{
	invalidateRegionSequenceViews();
}

void DocumentView::willRemoveRegionSequenceFromDocument (juce::ARADocument*, juce::ARARegionSequence* regionSequence)
{
	removeRegionSequenceView (regionSequence);
}

void DocumentView::didEndEditing (juce::ARADocument*)
{
	rebuildRegionSequenceViews();
	updateViewport();
}

//==============================================================================
void DocumentView::changeListenerCallback (juce::ChangeBroadcaster*)
{
	updateViewport();
}

//==============================================================================
// ARAEditorView::Listener overrides
void DocumentView::onNewSelection (const ARA::PlugIn::ViewSelection&)
{
	DBG("NEW SELECTION");
}

void DocumentView::onHideRegionSequences (const std::vector<juce::ARARegionSequence*>& regionSequences)
{
	DBG("NEW SELECTION");
}


void DocumentView::paint (juce::Graphics& g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::red);
	g.drawRect(outline, 2.f);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Doc Controller View",
					  getLocalBounds(),
					  Justification::centred,
					  1);
}

void DocumentView::resized()
{
	auto bounds = getLocalBounds();
	const auto bottomControlsBounds = bounds.removeFromBottom (40);
	const auto headerBounds = bounds.removeFromLeft (headerWidth).reduced (2);

	zoomControls.setBounds (bottomControlsBounds);
	layOutVertically (headerBounds, trackHeaders, viewportHeightOffset);
	tracksBackground.setBounds (bounds);
	viewport.setBounds (bounds);
	overlay.setBounds (bounds);
	
	for (auto& view : regionSequenceViews)
	{
		auto regionSequenceView = view.second.get();
		regionSequenceView->resized();
	}
}


void DocumentView::setZoomLevel (double pixelPerSecond)
{
	zoomLevelPixelPerSecond = pixelPerSecond;

	for (const auto& view : regionSequenceViews)
		view.second->setZoomLevel (zoomLevelPixelPerSecond);

	overlay.setZoomLevel (zoomLevelPixelPerSecond);

	updateViewport();
}


//=============================
// PRIVATE FUNCTIONS
void DocumentView::zoom (double factor)
{
	zoomLevelPixelPerSecond = jlimit (minimumZoom, minimumZoom * 32, zoomLevelPixelPerSecond * factor);
	setZoomLevel (zoomLevelPixelPerSecond);
}



void DocumentView::updateViewport()
{
	timelineLength = 0.0;

	for (const auto& view : regionSequenceViews)
		timelineLength = std::max (timelineLength, view.second->getPlaybackDuration());

	auto timelineWidth = roundToInt (timelineLength * zoomLevelPixelPerSecond);
	auto timelineHeight = roundToInt ((int) regionSequenceViews.size() * trackHeight);
	
	viewport.content.setSize (timelineWidth, timelineHeight);
	viewport.content.resized();

	resized();
}

void DocumentView::addTrackViews (juce::ARARegionSequence* regionSequence)
{
	const auto insertIntoMap = [](auto& map, auto key, auto value) -> auto&
	{
		auto it = map.insert ({ std::move (key), std::move (value) });
		return *(it.first->second);
	};

	auto& regionSequenceView = insertIntoMap (
		regionSequenceViews,
		RegionSequenceViewKey { regionSequence },
		std::make_unique<RegionSequenceView> (mEditor, *regionSequence, waveformCache, zoomLevelPixelPerSecond));

	regionSequenceView.addChangeListener (this);
	viewport.content.addAndMakeVisible (regionSequenceView);

	auto& trackHeader = insertIntoMap (trackHeaders,
									   RegionSequenceViewKey { regionSequence },
									   std::make_unique<TrackHeader> (*regionSequence));

	addAndMakeVisible (trackHeader);
	
	updateViewport();
}


void DocumentView::removeRegionSequenceView (juce::ARARegionSequence* regionSequence)
{
	const auto& view = regionSequenceViews.find (RegionSequenceViewKey { regionSequence });

	if (view != regionSequenceViews.cend())
	{
		removeChildComponent (view->second.get());
		regionSequenceViews.erase (view);
	}

	invalidateRegionSequenceViews();
}

void DocumentView::invalidateRegionSequenceViews()
{
	regionSequenceViewsAreValid = false;
	rebuildRegionSequenceViews();
}

void DocumentView::rebuildRegionSequenceViews()
{
	if (! regionSequenceViewsAreValid && ! araDocument.getDocumentController()->isHostEditingDocument())
	{
		for (auto& view : regionSequenceViews)
			removeChildComponent (view.second.get());

		regionSequenceViews.clear();

		for (auto& view : trackHeaders)
			removeChildComponent (view.second.get());

		trackHeaders.clear();

		for (auto* regionSequence : araDocument.getRegionSequences())
		{
			addTrackViews (regionSequence);
		}

		updateViewport();

		regionSequenceViewsAreValid = true;
	}
}
