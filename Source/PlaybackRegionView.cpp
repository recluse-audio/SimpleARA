/*
  ==============================================================================

    PlaybackRegionView.cpp
    Created: 1 Nov 2022 12:47:47pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaybackRegionView.h"
#include "ActiveRegionView.h"
#include "AudioModView.h"
#include "AudioSourceView.h"

#include "ARA_DocumentSpecialisation.h"
#include "ARA_PlaybackRegion.h"
#include "GlobalDefines.h"
#include "WaveformCache.h"
#include "PluginEditor.h"
#include "HelperDisplay.h"
#include "PluginProcessor.h"
#include "ARA_AudioMod.h"

//==============================================================================
PlaybackRegionView::PlaybackRegionView(SimpleARAEditor& editor, ARA_PlaybackRegion& region, WaveformCache& cache)
: mEditor(editor), playbackRegion (region), waveformCache (cache)
{
	
	auto* audioSource = playbackRegion.getAudioModification()->getAudioSource();

	//waveformCache.getOrCreateThumbnail (audioSource).addChangeListener (this);
	
	
	audioSourceView = std::make_unique<AudioSourceView>(mEditor, *audioSource, waveformCache);
	addAndMakeVisible(audioSourceView.get());
	
	audioModView = std::make_unique<AudioModView>(mEditor, playbackRegion);
	addAndMakeVisible(audioModView.get());
	
	activeRegionView = std::make_unique<ActiveRegionView>(mEditor, playbackRegion, waveformCache);
	addAndMakeVisible(activeRegionView.get());
	
    slider = std::make_unique<juce::Slider>();
    addAndMakeVisible(slider.get());
    
    auto processor = mEditor.getSimpleAudioProcessor();
    auto gainParam = playbackRegion.getAudioModification<ARA_AudioMod>()->getGainParam();
    sliderAttachment = std::make_unique<juce::SliderParameterAttachment>(*gainParam, *slider.get());
    
	playbackRegion.addListener(this);
	
}

//-------------------------------------
PlaybackRegionView::~PlaybackRegionView()
{
//	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
//		.removeChangeListener (this);
	
	playbackRegion.removeListener(this);
}


//-------------------------------------
void PlaybackRegionView::changeListenerCallback(juce::ChangeBroadcaster* changeBroadcaster)
{
	repaint();
}


//-------------------------------------
void PlaybackRegionView::paint (juce::Graphics& g)
{

	
//	auto bounds = this->getLocalBounds();
//
//	_drawPlaybackRegion(g);
//
//	g.drawRect(bounds, 2.f);

}



//-------------------------------------
void PlaybackRegionView::resized()
{
	_updateRegionBounds();
	
	repaint();
    activeRegionView->repaint();
    
    slider->setBoundsRelative(0.1f, 0.3f, 0.8f, 0.4f);
}



//-------------------------------------
void PlaybackRegionView::_updateRegionBounds()
{
	auto audioSourceBounds = this->getLocalBounds();
	auto audioModBounds = audioSourceBounds.reduced(2);
	audioSourceView->setBounds(audioSourceBounds);
	audioModView->setBounds(audioModBounds);
	
	auto audioSource = playbackRegion.getAudioModification()->getAudioSource();
	auto sourceDuration = audioSource->getDuration();
	
	auto regionStartInMod = playbackRegion.getStartInAudioModificationTime();
	auto regionDurationInMod = playbackRegion.getDurationInAudioModificationTime();
	
	auto regionStartInBounds = ( regionStartInMod   / sourceDuration ) * audioModBounds.getWidth();
	auto regionWidthInBounds = ( regionDurationInMod / sourceDuration ) * audioModBounds.getWidth();
	
	auto activeRegionBounds = juce::Rectangle<int>(regionStartInBounds, audioModBounds.getY(), regionWidthInBounds, audioModBounds.getHeight());
	
	activeRegionView->setBounds(activeRegionBounds);
}


void PlaybackRegionView::mouseEnter(const juce::MouseEvent& e)
{
	auto helperDisplay = mEditor.getHelperDisplay();
	helperDisplay->displayPlaybackRegion(&playbackRegion);

}

void PlaybackRegionView::mouseExit(const juce::MouseEvent& e)
{
}

void PlaybackRegionView::mouseDown(const juce::MouseEvent& e)
{
	
}



void PlaybackRegionView::didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion* pRegion)
{
	if(&playbackRegion == pRegion)
    {
        resized();
        repaint();
    }
}
