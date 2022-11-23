/*
  ==============================================================================

    AudioModView.h
    Created: 20 Nov 2022 3:24:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveformCache.h"

//==============================================================================
/*
*/
class AudioModView  : public juce::Component//, public juce::ChangeListener, public juce::ARAPlaybackRegion::Listener
{
public:
	AudioModView();
    //AudioModView(juce::ARAPlaybackRegion& region, WaveformCache& cache);
    ~AudioModView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
//	juce::ARAPlaybackRegion& playbackRegion;
//	WaveformCache& waveformCache;
	
	void _drawAudioMod(juce::Graphics& g);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioModView)
};
