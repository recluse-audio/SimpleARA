/*
  ==============================================================================

    SequenceHeaderContent.h
    Created: 2 Jan 2023 12:18:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ARAViewSection.h"

class ZoomState;
class SequenceHeader;
//==============================================================================
/*
    Content for a viewport that allows vertical (but not horizontal) scrolling of headers associated with a given ARA region sequence
*/
class SequenceHeaderContent  : public juce::Component
{
public:
    SequenceHeaderContent(ARAViewSection& section, juce::ARADocument& document);
    ~SequenceHeaderContent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // Makes a header to match a given region sequence
    void addRegionSequence(juce::ARARegionSequence* sequence);
    void clear()
    {
        headers.clear();
        this->deleteAllChildren();
    }
    void updateZoomState();
private:
    ARAViewSection& araSection;
    juce::ARADocument& araDocument;
    
    juce::OwnedArray<SequenceHeader> headers;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceHeaderContent)
};
