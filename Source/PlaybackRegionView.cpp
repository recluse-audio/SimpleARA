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
#include "ARAViewSection.h"

#include "ARA_DocumentSpecialisation.h"
#include "ARA_PlaybackRegion.h"
#include "GlobalDefines.h"
#include "WaveformCache.h"
#include "PluginEditor.h"
#include "HelperDisplay.h"
#include "PluginProcessor.h"
#include "ARA_AudioMod.h"
#include "ZoomState.h"

//==============================================================================
PlaybackRegionView::PlaybackRegionView(ARAViewSection& section, ARA_PlaybackRegion& region)
: araSection(section)
, playbackRegion(region)
, zoomState(araSection.getZoomState())
{
	
	// auto* audioSource = playbackRegion.getAudioModification()->getAudioSource();

	// waveformCache.getOrCreateThumbnail (audioSource).addChangeListener (this);
	
	audioSourceView = std::make_unique<AudioSourceView>(araSection, *region.getAudioModification()->getAudioSource());
	addAndMakeVisible(audioSourceView.get());
	
	audioModView = std::make_unique<AudioModView>(araSection, *region.getAudioModification<ARA_AudioMod>());
	addAndMakeVisible(audioModView.get());
	
	activeRegionView = std::make_unique<ActiveRegionView>(araSection, playbackRegion);
	addAndMakeVisible(activeRegionView.get());
	
    slider = std::make_unique<juce::Slider>();
    slider->setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    slider->setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::grey);
    slider->setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);

    addAndMakeVisible(slider.get());
    
    auto processor = araSection.getEditor().getSimpleAudioProcessor();
    auto audioMod = playbackRegion.getAudioModification<ARA_AudioMod>();
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    sliderAttachment = std::make_unique<Attachment>(audioMod->getValueTreeState(), "GAIN", *slider.get());
    
	playbackRegion.addListener(this);
	zoomState.addChangeListener(this);

	updateZoomState();
	
}

//-------------------------------------
PlaybackRegionView::~PlaybackRegionView()
{
//	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
//		.removeChangeListener (this);
	
	playbackRegion.removeListener(this);
	zoomState.removeChangeListener(this);

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


void PlaybackRegionView::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if(source == &zoomState)
		updateZoomState();
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
	auto helperDisplay = araSection.getEditor().getHelperDisplay();
	helperDisplay->displayPlaybackRegion(playbackRegion);

}

void PlaybackRegionView::mouseExit(const juce::MouseEvent& e)
{
    auto helperDisplay = araSection.getEditor().getHelperDisplay();
    helperDisplay->clearDisplay();
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


//==============
void PlaybackRegionView::updateZoomState()
{
    auto duration = playbackRegion.getAudioSourceDuration();
    auto width = duration * araSection.getZoomState().getPixelsPerSecond();
    auto height = araSection.getZoomState().getTrackHeight();
    
    this->setSize(width, height);
}


//=============
juce::Range<double> PlaybackRegionView::getActiveRegionTimeRange() const
{
	auto start = playbackRegion.getStartInPlaybackTime();
	auto end = playbackRegion.getEndInPlaybackTime();
	return juce::Range<double>(start, end);
}


//=============
juce::Range<double> PlaybackRegionView::getFullRegionTimeRange() const
{
	return playbackRegion.getFullRegionTimeRange();
}
