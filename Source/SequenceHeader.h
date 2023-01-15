/*
  ==============================================================================

    SequenceHeader.h
    Created: 13 Jan 2023 3:09:48pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ARAViewSection;
class ZoomState;
//==============================================================================
/**
 A juce::Label for the "header" of a region sequence.  Essentially the track name.
 Functionally, this is a juce label that remembers which ara region sequence object it corresponds with
 
*/
class SequenceHeader  : public juce::Component
{
public:
    SequenceHeader(ARAViewSection& section, juce::ARARegionSequence& sequence);
    ~SequenceHeader() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateZoomState();

private:
    ARAViewSection& araSection;
    juce::ARARegionSequence& regionSequence;
    
    std::unique_ptr<juce::Label> sequenceLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceHeader)
};
