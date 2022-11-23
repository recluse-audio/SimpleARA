/*
  ==============================================================================

    TrackHeader.cpp
    Created: 1 Nov 2022 12:48:57pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackHeader.h"

//==============================================================================
TrackHeader::TrackHeader(const juce::ARARegionSequence& regionSequenceIn) : regionSequence (regionSequenceIn)
{
	update();

	addAndMakeVisible (trackNameLabel);
}

void TrackHeader::paint (juce::Graphics& g)
{
	g.setColour (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	g.fillRoundedRectangle (getLocalBounds().reduced (2).toType<float>(), 6.0f);
	g.setColour (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).contrasting());
	g.drawRoundedRectangle (getLocalBounds().reduced (2).toType<float>(), 6.0f, 1.0f);
}

void TrackHeader::resized()
{
	trackNameLabel.setBounds (getLocalBounds().reduced (2));

}


//========================
// PRIVATE FUNCTIONS
void TrackHeader::update()
{
	const auto getWithDefaultValue =
		[] (const ARA::PlugIn::OptionalProperty<ARA::ARAUtf8String>& optional, juce::String defaultValue)
	{
		if (const ARA::ARAUtf8String value = optional)
			return juce::String (value);

		return defaultValue;
	};

	trackNameLabel.setText (getWithDefaultValue (regionSequence.getName(), "No track name"),
							juce::NotificationType::dontSendNotification);
}
