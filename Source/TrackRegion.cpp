/*
  ==============================================================================

    TrackRegion.cpp
    Created: 16 Dec 2022 6:15:52pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackRegion.h"
#include "MultiTrackTimeline.h"

//==============================================================================
TrackRegion::TrackRegion()
{
    rangeInSeconds = std::make_unique<juce::Range<double>>(0, 1);

}

TrackRegion::~TrackRegion()
{
}

void TrackRegion::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::aqua.darker());
    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 2.f, 2.f);
}

void TrackRegion::resized()
{

}



//=======================
juce::Range<double>* TrackRegion::getRangeInSeconds() const
{
    return rangeInSeconds.get();
}

//=======================
double TrackRegion::getDuration() const
{
    return rangeInSeconds->getLength();
}


