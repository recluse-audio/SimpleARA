/*
  ==============================================================================

    PlayheadMarker.h
    Created: 21 Dec 2022 4:53:00pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayheadMarker  : public juce::Component
{
public:
    PlayheadMarker()
    {


    }

    ~PlayheadMarker() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        auto yellow = juce::Colours::yellow;
        auto h = this->getHeight();
        auto w = this->getWidth();
        auto gradient = juce::ColourGradient(yellow.withAlpha(0.1f), 0.f, h / 2.f, yellow, w, h / 2.f, false );
        g.setGradientFill(gradient);
        g.fillAll();
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayheadMarker)
};
