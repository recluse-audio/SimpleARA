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

//==============================================================================
RegionSequenceView::RegionSequenceView(ARAViewSection& section, juce::ARARegionSequence& sequence) :
araSection(section)
, regionSequence(sequence)
, zoomState(section.getZoomState())
{
	regionSequence.addListener (this);

    rebuild();

	updatePlaybackDuration();
}

RegionSequenceView::~RegionSequenceView()
{
	regionSequence.removeListener (this);


}

void RegionSequenceView::paint(juce::Graphics &g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::yellow.withAlpha(0.1f));
	g.fillRect(outline);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Region Sequence View", getLocalBounds(), Justification::centred, 1);
}

//==============================================================================
// ARA Document change callback overrides
void RegionSequenceView::willRemovePlaybackRegionFromRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	updatePlaybackDuration();
}

void RegionSequenceView::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	_createAndAddPlaybackRegionView (playbackRegion);
	updatePlaybackDuration();
}

void RegionSequenceView::willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	updatePlaybackDuration();
}

void RegionSequenceView::willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* playbackRegion, juce::ARAPlaybackRegion::PropertiesPtr regionProperties)
{
}

void RegionSequenceView::didUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion*)
{
	updatePlaybackDuration();
}

void RegionSequenceView::resized()
{

}


double RegionSequenceView::getPlaybackDuration() const noexcept
{
	return playbackDuration;
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


void RegionSequenceView::updatePlaybackDuration()
{

    resized();
}


//=================
void RegionSequenceView::updateZoomState()
{
    auto width = this->getPlaybackDuration() * zoomState.getPixelsPerSecond();
    auto height = zoomState.getTrackHeight();
    this->setSize(width, height);
}


//========================
// PRIVATE FUNCTIONS

void RegionSequenceView::_createAndAddPlaybackRegionView(juce::ARAPlaybackRegion *region)
{
    auto regionView = new PlaybackRegionView(araSection, *region);
    
    // don't re-add an existing view.  Happens due to weird timing of calls to ara listeners in different hosts
    if(playbackRegionViews.contains(regionView))
        return;
    
    this->addAndMakeVisible(regionView);
    playbackRegionViews.add(regionView);
    
}

void RegionSequenceView::_clearRegionViews()
{
    // Is this necessary or will calling clear also remove them as child components
    for(auto view : playbackRegionViews)
    {
        this->removeChildComponent(view);
    }
    
    playbackRegionViews.clear();
}



