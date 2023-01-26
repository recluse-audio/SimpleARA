/*
  ==============================================================================

    RegionSequenceView.h
    Created: 1 Nov 2022 12:48:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlaybackRegionView.h"
#include "WaveformCache.h"
#include "ARAViewSection.h"

class SimpleARAEditor;

//==============================================================================
/*
*/
class RegionSequenceView : public juce::Component,
public juce::ARARegionSequence::Listener,
private juce::ARAPlaybackRegion::Listener,
public juce::ChangeListener
{
public:
	RegionSequenceView (ARAViewSection& viewSection, juce::ARARegionSequence& sequence);

	~RegionSequenceView() override;

    //==============================================================================
    // ARA Document change callback overrides
    void willRemovePlaybackRegionFromRegionSequence (ARARegionSequence*, ARAPlaybackRegion* playbackRegion) override;
	void didAddPlaybackRegionToRegionSequence (ARARegionSequence*, ARAPlaybackRegion* playbackRegion) override;
	void willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion) override;
	void willUpdatePlaybackRegionProperties (ARAPlaybackRegion*, ARAPlaybackRegion::PropertiesPtr) override;
	void didUpdatePlaybackRegionProperties (ARAPlaybackRegion*) override;

    //===============================
	void resized() override;
	void paint(juce::Graphics& g) override;
	
	/** Returns the end timeline position in seconds of the last region in the sequence*/
	double getEndOfLastRegion() const;

    void updateZoomState();
    // clears out existing views, removing them as child components and deleting them, then re-adding them from the araDoc
    void rebuild();

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	
	int getOrderIndex() const;
	
private:
    ARAViewSection& araSection;
    juce::ARARegionSequence& regionSequence;
    ZoomState& zoomState;

    juce::OwnedArray<PlaybackRegionView> playbackRegionViews;
    

	void _updateEndOfLastRegion();

	double endOfLastRegion = 0.0;

    // creates a new playback region view
    void _createAndAddPlaybackRegionView(juce::ARAPlaybackRegion* region);
    
    // clears all region views from owned array and removes that view as a child component
    void _clearRegionViews();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RegionSequenceView)
};
