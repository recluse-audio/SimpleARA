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

//==============================================================================
/*
*/
class RegionSequenceView : public juce::Component,
public juce::ARARegionSequence::Listener,
public juce::ChangeBroadcaster,
private juce::ARAPlaybackRegion::Listener
{
public:
	RegionSequenceView (juce::ARARegionSequence& rs, WaveformCache& cache, double pixelPerSec);

	~RegionSequenceView() override;

    //==============================================================================
    // ARA Document change callback overrides
    void willRemovePlaybackRegionFromRegionSequence (ARARegionSequence*,
													 ARAPlaybackRegion* playbackRegion) override;

	void didAddPlaybackRegionToRegionSequence (ARARegionSequence*, ARAPlaybackRegion* playbackRegion) override;

	void willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion) override;

	void willUpdatePlaybackRegionProperties (ARAPlaybackRegion*, ARAPlaybackRegion::PropertiesPtr) override;

	void didUpdatePlaybackRegionProperties (ARAPlaybackRegion*) override;

	void resized() override;
	void paint(juce::Graphics& g) override;

	double getPlaybackDuration() const noexcept;
	void setZoomLevel (double pixelPerSecond);

private:
	void createAndAddPlaybackRegionView (ARAPlaybackRegion* playbackRegion);

	void updatePlaybackDuration();

    juce::ARARegionSequence& regionSequence;
	WaveformCache& waveformCache;
	std::unordered_map<juce::ARAPlaybackRegion*, std::unique_ptr<PlaybackRegionView>> playbackRegionViewsMap;
    double playbackDuration = 0.0;
    double zoomLevelPixelPerSecond;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RegionSequenceView)
};
