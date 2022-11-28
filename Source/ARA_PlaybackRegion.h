/*
  ==============================================================================

    ARA_PlaybackRegion.h
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ARA_PlaybackRegion : public juce::ARAPlaybackRegion
{
public:
    using juce::ARAPlaybackRegion::ARAPlaybackRegion;
    void setCurrentlyInView(bool inView);
    bool isCurrentlyInView() const;
private:
    bool currentlyInView = false;
    juce::Colour modColor;
};
