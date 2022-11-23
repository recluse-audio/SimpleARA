/*
  ==============================================================================

    AudioSourceView.cpp
    Created: 20 Nov 2022 5:26:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioSourceView.h"
#include "WaveformCache.h"

//==============================================================================
AudioSourceView::AudioSourceView(juce::ARAAudioSource& source, WaveformCache& cache)
: audioSource(source), waveCache(cache)
{
	waveCache.getOrCreateThumbnail(&audioSource);

}

AudioSourceView::~AudioSourceView()
{
}

void AudioSourceView::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::darkgrey);
	_drawAudioSource(g);
}

void AudioSourceView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AudioSourceView::_drawAudioSource(juce::Graphics& g)
{
	auto bounds = this->getLocalBounds();

	auto& thumbnail = waveCache.getOrCreateThumbnail(&audioSource);

	auto sourceDuration = audioSource.getDuration();

	// Draw full audio source
	g.setColour (Colours::whitesmoke.darker().withAlpha(0.3f));
	thumbnail.drawChannels (g, bounds, 0, sourceDuration, 1.0f);
}
