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
#include "GlobalDefines.h"
#include "WaveformCache.h"


//==============================================================================
PlaybackRegionView::PlaybackRegionView(ARAPlaybackRegion& region, WaveformCache& cache)
: playbackRegion (region), waveformCache (cache)
{
	
	auto* audioSource = playbackRegion.getAudioModification()->getAudioSource();

	waveformCache.getOrCreateThumbnail (audioSource).addChangeListener (this);
	
	
	audioSourceView = std::make_unique<AudioSourceView>(*audioSource, waveformCache);
	addAndMakeVisible(audioSourceView.get());
	
	audioModView = std::make_unique<AudioModView>();
	addAndMakeVisible(audioModView.get());
	
	activeRegionView = std::make_unique<ActiveRegionView>(playbackRegion, waveformCache);
	addAndMakeVisible(activeRegionView.get());
	
	
	juce::String regionAddress = HexStringForPointer(&region);
	juce::String labelText ("Memory Address: ");
	memoryAddressLabel = std::make_unique<juce::Label>("MEMORY ADDRESS LABEL", labelText + regionAddress);
	memoryAddressLabel->setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
	addAndMakeVisible(memoryAddressLabel.get());
	
	notificationLabel = std::make_unique<juce::Label>();
	addAndMakeVisible(notificationLabel.get());
	
	playbackRegion.addListener(this);
}

//-------------------------------------
PlaybackRegionView::~PlaybackRegionView()
{
	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
		.removeChangeListener (this);
	
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
	g.fillAll (Colours::darkgrey.darker(0.9f));
	
//	auto bounds = this->getLocalBounds();
//
//	_drawPlaybackRegion(g);
//
//	g.drawRect(bounds, 2.f);

}




//-------------------------------------
void PlaybackRegionView::updateAddressLabel(juce::StringRef newAddress)
{
	juce::String labelText("Playback Region - Memory Address: ");
	memoryAddressLabel->setText(labelText + newAddress, juce::NotificationType::sendNotification);
}

//-------------------------------------
void PlaybackRegionView::resized()
{
	memoryAddressLabel->setBoundsRelative(0.05f, 0.65f, 0.4f, 0.25f);
	notificationLabel->setBoundsRelative(0.5f, 0.65f, 0.4f, 0.25f);
	
	_updateRegionBounds();
	
	repaint();
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





//***********************
// ARA LISTENER CALLBACKS
void PlaybackRegionView::willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* updatedRegion, ARA::PlugIn::PropertiesPtr<ARA::ARAPlaybackRegionProperties> newProperties)
{
	if(&playbackRegion == updatedRegion)
	{
		notificationLabel->setText("willUpdatePlaybackRegionProperties();", juce::NotificationType::sendNotificationAsync);
		_updateRegionBounds();
		repaint();
	}
	
}

//-------------------------------------
void PlaybackRegionView::didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion* updatedRegion)
{
	if(&playbackRegion == updatedRegion)
	{
		notificationLabel->setText("didUpdatePlaybackRegionProperties();", juce::NotificationType::sendNotificationAsync);
		_updateRegionBounds();
		repaint();
	}

}

void PlaybackRegionView::didUpdatePlaybackRegionContent (juce::ARAPlaybackRegion* updatedRegion, juce::ARAContentUpdateScopes scopeFlags)
{
	if(&playbackRegion == updatedRegion)
	{
		notificationLabel->setText("didUpdatePlaybackRegionContent();", juce::NotificationType::sendNotificationAsync);
		_updateRegionBounds();
		repaint();
	}}

void PlaybackRegionView::willDestroyPlaybackRegion (juce::ARAPlaybackRegion* regionToDestroy)
{
	if(&playbackRegion == regionToDestroy)
	{
		notificationLabel->setText("willDestroyPlaybackRegion();", juce::NotificationType::sendNotificationAsync);
		_updateRegionBounds();
		repaint();
	}
}


