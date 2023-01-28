/*
  ==============================================================================

    RegionSequenceView.cpp
    Created: 1 Nov 2022 12:48:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RegionSequenceView.h"
#include "ARA_PlaybackRegion.h"
#include "GlobalDefines.h"
#include "PluginEditor.h"
#include "ZoomState.h"
//==============================================================================
RegionSequenceView::RegionSequenceView(ARAViewSection& section, juce::ARARegionSequence& sequence) :
araSection(section)
, regionSequence(sequence)
, zoomState(section.getZoomState())
{
	regionSequence.addListener (this);
	zoomState.addChangeListener(this);

    rebuild();

	_updateEndOfLastRegion();
	
	updateZoomState();

}

RegionSequenceView::~RegionSequenceView()
{
	regionSequence.removeListener (this);
	araSection.removeChangeListener(this);


}

void RegionSequenceView::paint(juce::Graphics &g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::yellow);
	g.fillRect(outline);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Region Sequence View", getLocalBounds(), Justification::centred, 1);
}


//=================
void RegionSequenceView::resized()
{

	for(auto regionView : playbackRegionViews)
	{
		auto regionTimeRange = regionView->getFullRegionTimeRange();
		auto startPixel = regionTimeRange.getStart() * zoomState.getPixelsPerSecond();
		regionView->setTopLeftPosition(startPixel, 0);
	}
}

//=================
double RegionSequenceView::getEndOfLastRegion() const
{
	return endOfLastRegion;
}



//=================
void RegionSequenceView::rebuild()
{
    _clearRegionViews();
    
    auto regions = regionSequence.getPlaybackRegions<ARA_PlaybackRegion>();
    for(auto region : regions)
    {
        _createAndAddPlaybackRegionView(region);
    }
    
}



//=================
void RegionSequenceView::updateZoomState()
{
	_updateEndOfLastRegion();
    auto width = getEndOfLastRegion() * zoomState.getPixelsPerSecond();
    auto height = zoomState.getTrackHeight();
    this->setSize(width, height);
}


//========================
// PRIVATE FUNCTIONS

//=================
void RegionSequenceView::_updateEndOfLastRegion()
{
	for(auto region : regionSequence.getPlaybackRegions<ARA_PlaybackRegion>())
	{
		if(region->getEndInPlaybackTime() > endOfLastRegion )
		{
			endOfLastRegion = region->getEndInPlaybackTime();
		}
	}
}

//=================
void RegionSequenceView::_createAndAddPlaybackRegionView(juce::ARAPlaybackRegion *region)
{
    auto pRegion = dynamic_cast<ARA_PlaybackRegion*>(region);
    auto regionView = new PlaybackRegionView(araSection, *pRegion);
    
    // don't re-add an existing view.  Happens due to weird timing of calls to ara listeners in different hosts
    if(playbackRegionViews.contains(regionView))
        return;
    
    this->addAndMakeVisible(regionView);
    playbackRegionViews.add(regionView);
	resized();
    
}

//=================
void RegionSequenceView::_clearRegionViews()
{
    // Is this necessary or will calling clear also remove them as child components
    for(auto view : playbackRegionViews)
    {
        this->removeChildComponent(view);
    }
    
    playbackRegionViews.clear();
}


//==================
void RegionSequenceView::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if(source == &zoomState)
		updateZoomState();
}


//==============================================================================
// ARA Document change callback overrides
//=================
void RegionSequenceView::willRemovePlaybackRegionFromRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	_updateEndOfLastRegion();
}

//=================
void RegionSequenceView::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	_createAndAddPlaybackRegionView (playbackRegion);
	_updateEndOfLastRegion();
	updateZoomState();

}

//=================
void RegionSequenceView::willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	_updateEndOfLastRegion();
}

//=================
void RegionSequenceView::willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* playbackRegion, juce::ARAPlaybackRegion::PropertiesPtr regionProperties)
{

}

void RegionSequenceView::didUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion*)
{
	updateZoomState();

}


//======================
int RegionSequenceView::getOrderIndex() const
{
	return regionSequence.getOrderIndex();
}
