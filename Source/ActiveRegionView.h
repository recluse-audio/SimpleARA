/*
  ==============================================================================

    ActiveRegionView.h
    Created: 20 Nov 2022 5:21:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class WaveformCache;

//==============================================================================
/**
	This class represents the Playback Region that is only the duration as it appears on the timeline
	
	see PlaybackRegionView
*/
class ActiveRegionView  : public juce::Component
{
public:
    ActiveRegionView(juce::ARAPlaybackRegion& region, WaveformCache& cache);
    ~ActiveRegionView() override;
	
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::ARAPlaybackRegion& playbackRegion;
	WaveformCache& waveCache;
	
	void _drawPlaybackRegion(juce::Graphics& g);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ActiveRegionView)
};
