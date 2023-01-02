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
TrackRegion::TrackRegion(MultiTrackTimeline& timeLine, double startPos, double duration)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
{
    rangeInSeconds = std::make_unique<juce::Range<double>>(startPos, startPos +  duration);

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

//=======================
void TrackRegion::updateZoomState()
{
    const auto pixPerSecond = mTimeline.getZoomState().getPixelsPerSecond();
    auto regionWidth = this->getDuration() * pixPerSecond;
    auto regionHeight = mTimeline.getZoomState().getTrackHeight();
    this->setSize(regionWidth, regionHeight);
}
