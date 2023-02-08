/*
  ==============================================================================

    ARAViewSection.cpp
    Created: 2 Dec 2022 6:42:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARAViewSection.h"
#include "DocumentView.h"
#include "PlaybackRegionView.h"
#include "WaveformCache.h"
#include "ARA_DocumentSpecialisation.h"
#include "PluginEditor.h"
#include "ARA_PlaybackRegion.h"
#include "MultiTrackTimeline.h"
#include "TrackLane.h"
#include "TimeRuler.h"
#include "SequenceHeader.h"
#include "SequenceHeaderContent.h"
#include "RegionSequenceView.h"
#include "ZoomControls.h"



//==============================================================================
ARAViewSection::ARAViewSection(SimpleARAEditor& editor) : mEditor(editor)
, playheadState(editor.getPlayHeadState())
{
	// must initialize before all the views... don't like this, should change
	zoomState = std::make_unique<ZoomState>(*this);
	
	
    waveCache = std::make_unique<WaveformCache>();
    
    timeRulerContent = std::make_unique<TimeRuler>(*this);
    timeRulerViewport = std::make_unique<juce::Viewport>();
    timeRulerViewport->setViewedComponent(timeRulerContent.get());
	timeRulerViewport->setScrollBarsShown(false, false);
    addAndMakeVisible(timeRulerViewport.get());
    
    
    auto document = mEditor.getARADocument();
    
    if(document != nullptr)
	{
//		auto docSpecialisation = mEditor.getARADocumentSpecialisation();

		documentContent = std::make_unique<DocumentView> (*this, *document);
		documentViewport = std::make_unique<juce::Viewport>();
		documentViewport->setViewedComponent(documentContent.get());
		addAndMakeVisible(documentViewport.get());
		
		headerContent = std::make_unique<SequenceHeaderContent>(*this, *document);
		headerViewport = std::make_unique<juce::Viewport>();
		headerViewport->setViewedComponent(headerContent.get());
		headerViewport->setScrollBarsShown(false, false);
		addAndMakeVisible(headerViewport.get());

	}
	
	
	mEditor.getARAEditorView()->addListener(this);
	mEditor.getARADocument()->addListener(this);
	
	zoomControls = std::make_unique<ZoomControls>(*zoomState.get());
	addAndMakeVisible(zoomControls.get());

	vertZoomControls = std::make_unique<ZoomControls>(*zoomState.get());
	vertZoomControls->setVertical(true);
	addAndMakeVisible(vertZoomControls.get());
    
	documentViewport->getHorizontalScrollBar().addListener(this);
	documentViewport->getVerticalScrollBar().addListener(this);
	
	
	_rebuildFromDocument();

	zoomState->transformVerticalZoomByPercent(0.0);
	
 //   this->startTimerHz(60);
	
	auto docSpecialisation = mEditor.getARADocumentSpecialisation();
	auto viewPosition = docSpecialisation->getViewportPosition();
	this->setViewportPosition(viewPosition.getX(), viewPosition.getY());
    
}

ARAViewSection::~ARAViewSection()
{
	
	documentViewport->getHorizontalScrollBar().removeListener(this);
	documentViewport->getVerticalScrollBar().removeListener(this);
	mEditor.getARAEditorView()->removeListener(this);
	mEditor.getARADocument()->removeListener(this);

}

void ARAViewSection::_initializeViews(juce::ARADocument* document)
{
    auto docSpecialisation = mEditor.getARADocumentSpecialisation();

    documentContent = std::make_unique<DocumentView> (*this, *document);
    documentViewport = std::make_unique<juce::Viewport>();
    documentViewport->setViewedComponent(documentContent.get());
    addAndMakeVisible(documentViewport.get());
    
    headerContent = std::make_unique<SequenceHeaderContent>(*this, *document);
    headerViewport = std::make_unique<juce::Viewport>();
    headerViewport->setViewedComponent(headerContent.get());
	headerViewport->setScrollBarsShown(false, false);
    addAndMakeVisible(headerViewport.get());
//
//    /** TO DO : make regionZero into the last selected region */
//    auto regionZero = static_cast<ARA_PlaybackRegion*>(docSpecialisation->getRegionAtIndex(0));
//    playbackRegionView = std::make_unique<PlaybackRegionView>(mEditor, *regionZero, *waveCache.get() );
//    addChildComponent(playbackRegionView.get());
}

//==================
void ARAViewSection::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey.withAlpha(1.f));
}

void ARAViewSection::resized()
{
    auto bounds = this->getLocalBounds();
    auto localWidth = bounds.getWidth();
    auto localHeight = bounds.getHeight();;
    auto headerWidth = zoomState->getHeaderWidth();
    auto trackHeight = zoomState->getTrackHeight();
    auto timeRulerHeight = zoomState->getTimeRulerHeight();
    auto widthMinusHeader = localWidth - headerWidth;
    auto heightMinusRuler = localHeight - timeRulerHeight;
    
    headerViewport->setBounds   (0, timeRulerHeight, headerWidth, heightMinusRuler);
    timeRulerViewport->setBounds(headerWidth, 0, widthMinusHeader, timeRulerHeight);
    documentViewport->setBounds(headerWidth, timeRulerHeight, widthMinusHeader, heightMinusRuler);

	
	zoomControls->setBounds(localWidth - 100, localHeight - 40, 90, 30);
	vertZoomControls->setBounds(localWidth - 40, localHeight - 140, 30, 90);
}

//========================
//void ARAViewSection::setFocus(SimpleARAEditor::FocusView focus)
//{
////    switch(focus)
////    {
////        case 0:
////            documentView->setVisible(true);
////            playbackRegionView->setVisible(false);
////        case 1:
////            documentView->setVisible(false);
////            playbackRegionView->setVisible(true);
////    }
//}

//=======================
void ARAViewSection::setDocumentFocus()
{
    //documentView->setVisible(true);
    //playbackRegionView->setVisible(false);
}

//=======================
void ARAViewSection::setSequenceFocus()
{
    
}

//=======================
void ARAViewSection::setRegionFocus()
{
    //documentView->setVisible(false);
    //playbackRegionView->setVisible(true);
}


//=======================
void ARAViewSection::_updateZoomState()
{


}

//======================
void ARAViewSection::timerCallback()
{
    documentContent->updatePlayheadPosition(playheadState.timeInSeconds);
}


//======================
juce::ARADocument& ARAViewSection::getARADocument()
{
    return *mEditor.getARADocument();
}

//======================
ZoomState& ARAViewSection::getZoomState()
{
    return *zoomState.get();
}

//=====================
SimpleARAEditor& ARAViewSection::getEditor()
{
    return mEditor;
}

//=====================
WaveformCache& ARAViewSection::getWaveCache()
{
    return *waveCache.get();
}







//======================
void ARAViewSection::didAddRegionSequenceToDocument (juce::ARADocument* doc, juce::ARARegionSequence* sequence)
{
    //_addRegionSequence(sequence);
}

//======================
void ARAViewSection::didEndEditing(juce::ARADocument *doc)
{
	//_rebuildFromDocument();
}

//==================
void ARAViewSection::onNewSelection(const juce::ARAViewSelection& newSelection)
{
	this->_unselectAll();
	auto effectiveRegions = newSelection.getEffectivePlaybackRegions<ARA_PlaybackRegion>();
	for(auto region : effectiveRegions)
	{
		region->setCurrentlySelected(true);
	}
	repaint();
	
}







// clears current
void ARAViewSection::_rebuildFromDocument()
{
    headerContent.reset();
    documentContent.reset();
    
    headerContent = std::make_unique<SequenceHeaderContent>(*this, *mEditor.getARADocument());
    documentContent = std::make_unique<DocumentView>(*this, *mEditor.getARADocument());
    
    auto regionSequences = mEditor.getARADocument()->getRegionSequences();
    for(auto sequence : regionSequences)
    {
        _addRegionSequence(sequence);
    }
	
	headerViewport->setViewedComponent(headerContent.get());
	documentViewport->setViewedComponent(documentContent.get());
	
	zoomState->triggerUpdate();
}

//======================
void ARAViewSection::_addRegionSequence(juce::ARARegionSequence* sequence)
{
    headerContent->addRegionSequence(sequence);
    documentContent->addRegionSequence(sequence);
}



//===================
void ARAViewSection::setViewportTimeRange(double startInSeconds, double durationInSeconds)
{
	// This will adjust how much of the timeline is visible at a given moment
	// This adjusts the pixPerSecond so do this first
	zoomState->zoomToShowDuration(this->getWidth(), durationInSeconds);
	viewportTimeRange.setStart(startInSeconds);
	viewportTimeRange.setEnd(startInSeconds + durationInSeconds);
	shouldUpdateViewport = true;
}

//==================
void ARAViewSection::setViewportEndPos(double endInSeconds)
{
	viewportTimeRange = viewportTimeRange.movedToEndAt(endInSeconds);
	shouldUpdateViewport = true;
}



//==================
void ARAViewSection::_unselectAll()
{
	auto allSequences = this->getARADocument().getRegionSequences();
	for(auto sequence : allSequences)
	{
		auto regions = sequence->getPlaybackRegions<ARA_PlaybackRegion>();
		for(auto region : regions)
		{
			region->setCurrentlySelected(false);
		}
	}
}

//==================
double ARAViewSection::getDuration() const
{
	return documentContent->getDuration();
}




//==================
void ARAViewSection::scrollBarMoved(juce::ScrollBar *scrollBar, double newRangeStart)
{
	if(!hasRestoredViewPosition)
	{
		hasRestoredViewPosition = true;
		return;
	}
	
	if(scrollBar == &documentViewport->getHorizontalScrollBar() || scrollBar == &documentViewport->getVerticalScrollBar())
	{
		auto viewPosX = documentViewport->getViewPositionX();
		auto viewPosY = documentViewport->getViewPositionY();
		timeRulerViewport->setViewPosition(viewPosX, 0);
		headerViewport->setViewPosition(0, viewPosY);
	}
	
}


///==================
void ARAViewSection::setViewportPosition(int x, int y)
{
	
	documentViewport->setViewPosition(x, y);
	timeRulerViewport->setViewPosition(x, 0);
	headerViewport->setViewPosition(0, y);
	
}

juce::Viewport* ARAViewSection::getDocumentViewport() const
{
	return documentViewport.get();
}
