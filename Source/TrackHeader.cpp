/*
  ==============================================================================

    TrackHeader.cpp
    Created: 1 Nov 2022 12:48:57pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackHeader.h"
#include "ZoomState.h"

//==============================================================================
TrackHeader::TrackHeader()
{
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


void TrackHeader::setName(juce::StringRef newName)
{
    trackNameLabel.setText(newName, juce::NotificationType::dontSendNotification);
}

//void TrackHeader::updateZoomState(ZoomState& zoomState)
//{
//    auto width = zoomState().getHeaderWidth();
//    auto height = zoomState().getTrackHeight();
//    this->setSize(width, height);
//}


