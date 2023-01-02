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
#include "MultiTrackTimeline.h"
#include "ZoomState.h"

//==============================================================================
TrackLane::TrackLane(MultiTrackTimeline& timeLine)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
{
    generateThreeRandomRegions();
}

TrackLane::TrackLane(MultiTrackTimeline& timeLine, int index)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
, orderIndex(index)
{
    generateThreeRandomRegions();
}

TrackLane::~TrackLane()
{
}

void TrackLane::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack.withAlpha(0.f));
//    g.drawText(juce::String(orderIndex), 0, 0, 30, this->getHeight(), juce::Justification::centred);
    g.setColour(juce::Colours::black);
    g.drawHorizontalLine(this->getHeight()-2, 0, this->getWidth());

}

void TrackLane::resized()
{
    for (auto region : regionArray)
    {
        
        auto range = region->getRangeInSeconds();
        
        auto startPos = range->getStart();
        auto duration = range->getLength();
        
        const auto pixPerSecond = mTimeline.getZoomState().getPixelsPerSecond();
        const auto xPos = roundToInt(startPos * pixPerSecond) + mTimeline.getTrackLabelWidth();
        region->setTopLeftPosition(xPos, 0);
        
//        const auto width = roundToInt (duration * pixPerSecond);
//        
//        auto regionBounds = juce::Rectangle<int>(xPos, 5, width, this->getHeight() - 10);
//        region->setBounds(regionBounds);
    }
}

void TrackLane::updateZoomState()
{
    for(auto region : regionArray)
    {
        region->updateZoomState();
    }
    
    const auto pixPerSecond = mTimeline.getZoomState().getPixelsPerSecond();
	auto trackWidth = this->getDuration() * pixPerSecond;
	auto trackHeight = mTimeline.getZoomState().getTrackHeight();
	this->setSize(trackWidth, trackHeight);
	
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
    regionArray.add(region);
    this->_updateDuration();
    resized();
}

// generate three regions max range of 5,
void TrackLane::generateThreeRandomRegions()
{
    for(int i = 0; i < 5; i++)
    {
        auto timelineOffset = i * 30;
        float randStart = juce::Random().nextInt(10) + timelineOffset;
        float randDur = juce::Random().nextInt(5);
        
        addRegion(new TrackRegion(mTimeline, randStart, randDur));
    }

}


//========================
void TrackLane::_updateDuration()
{
    for(auto region : regionArray)
    {
        auto regionRange = region->getRangeInSeconds();
        if(regionRange->getEnd() > duration)
            duration = regionRange->getEnd();
    }
}
