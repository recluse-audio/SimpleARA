/*
  ==============================================================================

    SequenceHeader.cpp
    Created: 13 Jan 2023 3:09:48pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SequenceHeader.h"
#include "ARAViewSection.h"
//==============================================================================
SequenceHeader::SequenceHeader(ARAViewSection& section, juce::ARARegionSequence& sequence)
: araSection(section)
, regionSequence(sequence)
{
    sequenceLabel = std::make_unique<juce::Label>();
    sequenceLabel->setText(juce::String(regionSequence.getName()), juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sequenceLabel.get());
}

SequenceHeader::~SequenceHeader()
{
    sequenceLabel.reset();
}

void SequenceHeader::paint (juce::Graphics& g)
{
    
}

void SequenceHeader::resized()
{
    sequenceLabel->setBounds(this->getLocalBounds());
}

void SequenceHeader::updateZoomState()
{
    auto width = araSection.getZoomState().getHeaderWidth();
    auto height = araSection.getZoomState().getTrackHeight();
    this->setSize(width, height);
}
