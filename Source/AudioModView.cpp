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
#include "ARAViewSection.h"
#include "HelperDisplay.h"
#include "ARA_PlaybackRegion.h"
#include "PluginEditor.h"

//==============================================================================


AudioModView::AudioModView(ARAViewSection& section, ARA_AudioMod& modification)
: araSection(section)
, audioMod(modification)
{
    
}


AudioModView::~AudioModView()
{

}

void AudioModView::paint (juce::Graphics& g)
{
	auto modColor = audioMod.getColor();
	g.fillAll(modColor.withAlpha(0.3f));


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

void AudioModView::mouseEnter(const juce::MouseEvent& e)
{

}

void AudioModView::mouseExit(const juce::MouseEvent& e)
{

	
}
