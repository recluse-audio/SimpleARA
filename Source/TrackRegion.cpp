/*
  ==============================================================================

    TrackRegion.cpp
    Created: 16 Dec 2022 6:15:52pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackRegion.h"

//==============================================================================
TrackRegion::TrackRegion(float startPos, float dur)
{
    rangeInSeconds = std::make_unique<juce::Range<float>>(startPos, startPos + dur);

}

TrackRegion::~TrackRegion()
{
}

void TrackRegion::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
}

void TrackRegion::resized()
{

}

//=======================
void TrackRegion::setZoomLevel(double zoomLevelPixPerSecond)
{
    
}

//=======================
juce::Range<float>* TrackRegion::getRangeInSeconds() const
{
    return rangeInSeconds.get();
}
