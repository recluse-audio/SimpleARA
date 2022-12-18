/*
  ==============================================================================

    TrackLane.cpp
    Created: 15 Dec 2022 6:31:50pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackLane.h"
#include "TrackRegion.h"

//==============================================================================
TrackLane::TrackLane(MultiTrackTimeLine& timeLine)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
{


}

TrackLane::TrackLane(MultiTrackTimeLine& timeLine, int index) : orderIndex(index)
{
    addRegion(new TrackRegion(1.f, 5.f));
    addRegion(new TrackRegion(7.f, 9.f));
    addRegion(new TrackRegion(11.f, 15.f));

}

TrackLane::~TrackLane()
{
}

void TrackLane::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkmagenta);
    g.setColour(juce::Colours::white);
    g.drawText(juce::String(orderIndex), 0, 0, 30, this->getHeight(), juce::Justification::centred);
    g.setColour(juce::Colours::black);
    g.drawHorizontalLine(this->getHeight()-2, 0, this->getWidth());

}

void TrackLane::resized()
{
    for (auto region : trackRegions)
    {
        
        auto range = region->getRangeInSeconds();
        
        auto startPos = range->getStart();
        auto duration = range->getLength();
        
        const auto xPos = roundToInt(startPos * zoomLevelPixelPerSecond);
        const auto width = roundToInt (duration * zoomLevelPixelPerSecond);
        
        auto regionBounds = juce::Rectangle<int>(xPos, 5, width, this->getHeight() - 10);
        region->setBounds(regionBounds);
    }
}

void TrackLane::setOrderIndex(int newIndex)
{
    orderIndex = newIndex;
}

int TrackLane::getOrderIndex() const
{
    return orderIndex;
}

float TrackLane::getDuration() const
{
    return duration;
}

void TrackLane::setZoomLevel(double pixelsPerSecond)
{
    zoomLevelPixelPerSecond = pixelsPerSecond;
}

void TrackLane::addRegion(TrackRegion *region)
{
    this->addAndMakeVisible(region);
    trackRegions.add(region);
    resized();
}

void TrackLane::updateZoomState()
{
	
}
