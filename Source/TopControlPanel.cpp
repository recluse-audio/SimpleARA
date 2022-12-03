/*
  ==============================================================================

    TopControlPanel.cpp
    Created: 2 Dec 2022 6:37:49pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TopControlPanel.h"

//==============================================================================
TopControlPanel::TopControlPanel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TopControlPanel::~TopControlPanel()
{
}

void TopControlPanel::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::aquamarine.darker().withAlpha(0.7f));
}

void TopControlPanel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
