/*
  ==============================================================================

    AudioSourceView.h
    Created: 20 Nov 2022 5:26:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class WaveformCache;
class SimpleARAEditor;
//==============================================================================
/*
*/
class AudioSourceView  : public juce::Component
{
public:
	AudioSourceView(SimpleARAEditor& editor, juce::ARAAudioSource& source, WaveformCache& cache);
    ~AudioSourceView() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	
	void mouseEnter(const juce::MouseEvent& e) override;
	void mouseExit(const juce::MouseEvent& e) override;

private:
	juce::ARAAudioSource& audioSource;
	WaveformCache& waveCache;
	SimpleARAEditor& mEditor;

	void _drawAudioSource(juce::Graphics& g);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSourceView)
};
