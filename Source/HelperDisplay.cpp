/*
  ==============================================================================

    HelperDisplay.cpp
    Created: 23 Nov 2022 4:31:26pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HelperDisplay.h"
#include "GlobalDefines.h"

//==============================================================================
HelperDisplay::HelperDisplay()
{
	displayLabel = std::make_unique<juce::Label>("DISPLAY LABEL");
	addAndMakeVisible(displayLabel.get());

}

HelperDisplay::~HelperDisplay()
{
}

void HelperDisplay::paint (juce::Graphics& g)
{

}

void HelperDisplay::resized()
{
	displayLabel->setBoundsRelative(0.f, 0.f, 1.f, 1.f);

}

void HelperDisplay::clearDisplay()
{
	displayLabel->setText("", juce::NotificationType::dontSendNotification);
}

void HelperDisplay::displayPlaybackRegion(juce::ARAPlaybackRegion *pRegion)
{
	if(pRegion == nullptr)
		return;
	
	auto audioSourceAddress = "Audio Source: " + HexStringForPointer(pRegion->getAudioModification()->getAudioSource()) + " -- " ;
	auto audioModAddress = "Audio Mod: " + HexStringForPointer(pRegion->getAudioModification()) + " -- ";
	auto playbackRegionAddress = "Playback Region: " + HexStringForPointer(pRegion);
	
	auto address = audioSourceAddress + audioModAddress + playbackRegionAddress;
	displayLabel->setText(address, juce::NotificationType::dontSendNotification);
}
