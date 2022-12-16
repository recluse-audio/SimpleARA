/*
  ==============================================================================

    TimeRuler.cpp
    Created: 14 Dec 2022 6:37:00pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeRuler.h"

//==============================================================================
TimeRuler::TimeRuler()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TimeRuler::~TimeRuler()
{
}

void TimeRuler::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::peru);
    g.fillAll();
}

void TimeRuler::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
