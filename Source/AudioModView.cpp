/*
  ==============================================================================

    AudioModView.cpp
    Created: 20 Nov 2022 3:24:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioModView.h"
#include "ARA_AudioMod.h"
//==============================================================================
//AudioModView::AudioModView(juce::ARAPlaybackRegion& region, WaveformCache& cache)
//: playbackRegion(region), waveformCache(cache)
//{
//	auto* audioSource = playbackRegion.getAudioModification()->getAudioSource();
//	waveformCache.getOrCreateThumbnail (audioSource).addChangeListener (this);
//}
//
//AudioModView::~AudioModView()
//{
//	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
//		.removeChangeListener (this);
//
//	playbackRegion.removeListener(this);
//}

AudioModView::AudioModView()
{

}

AudioModView::~AudioModView()
{
//	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
//		.removeChangeListener (this);
//
//	playbackRegion.removeListener(this);
}

void AudioModView::paint (juce::Graphics& g)
{
//	auto modColor = playbackRegion.getAudioModification<ARAHelper_AudioMod>()->getColor();
//	g.fillAll(modColor.withAlpha(0.3f));
	
	g.fillAll(juce::Colours::orange.withAlpha(0.1f));

}

void AudioModView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void AudioModView::_drawAudioMod(juce::Graphics &g)
{
//	auto bounds = this->getLocalBounds();
//
//	auto audioSource = playbackRegion.getAudioModification()->getAudioSource();
//	auto& thumbnail = waveformCache.getOrCreateThumbnail(audioSource);
//	
//	auto thumbnailHeight = bounds.proportionOfHeight(0.6f);
//	
//	auto sourceDuration = audioSource->getDuration();
//	
//	// Draw full audio source
//	auto audioSourceBounds = bounds.withHeight(thumbnailHeight);
//	g.setColour (Colours::whitesmoke.darker().withAlpha(0.3f));
//	thumbnail.drawChannels (g, audioSourceBounds, 0, sourceDuration, 1.0f);
}
