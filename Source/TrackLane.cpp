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

TrackLane::TrackLane(MultiTrackTimeLine& timeLine, int index)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
, orderIndex(index)
{
    addRegion(new TrackRegion(timeLine, 1.f, 5.f));
    addRegion(new TrackRegion(timeLine, 7.f, 9.f));
    addRegion(new TrackRegion(timeLine, 11.f, 15.f));

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

void TrackLane::updateZoomState()
{
	auto zoomState = mTimeLine.getZoomState();
	
	auto trackWidth = this->getDuration() * zoomState.getPixelsPerSecond();
	auto trackHeight = zoomState.getTrackHeight();
	this->setSize(trackWidth, trackHeight);
	
	
	resized();
	
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

void TrackLane::addRegion(TrackRegion *region)
{
    this->addAndMakeVisible(region);
    trackRegions.add(region);
    resized();
}


