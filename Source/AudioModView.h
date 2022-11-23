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

class PlaybackRegionView;
class SimpleARAEditor;
//==============================================================================
/*
*/
class AudioModView  : public juce::Component
{
public:
	AudioModView(SimpleARAEditor& editor, juce::ARAPlaybackRegion& region);
    ~AudioModView() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	
	void mouseEnter(const juce::MouseEvent& e) override;
	void mouseExit(const juce::MouseEvent& e) override;

private:
	juce::StringRef _getARAObjectAddressStrings();


	juce::ARAPlaybackRegion& playbackRegion;
	SimpleARAEditor& mEditor;
	
	void _drawAudioMod(juce::Graphics& g);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioModView)
};
