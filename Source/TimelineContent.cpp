/*
  ==============================================================================

    TimelineContent.cpp
    Created: 15 Dec 2022 7:29:07pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimelineContent.h"
#include "TrackLane.h"


//==============================================================================
TimelineContent::TimelineContent()
{


}

//===================
TimelineContent::~TimelineContent()
{
}

//===================
void TimelineContent::paint (juce::Graphics& g)
{

}

//===================
void TimelineContent::resized()
{
    auto bounds = this->getLocalBounds();

    for (auto* component : this->getChildren())
    {
        auto trackLane = dynamic_cast<TrackLane*>(component);
        if(!trackLane)
            continue;
        
        auto yPos = trackLane->getOrderIndex() * trackHeight;
        component->setBounds (0, yPos, bounds.getWidth(), trackHeight);
        component->resized();
    }

}

//====================
void TimelineContent::setTrackHeight(int newHeight)
{
    trackHeight = newHeight;
    resized();
}

//====================
void TimelineContent::updateZoomLevel(double wPixPerSecond, double hPixPerSecond)
{
    auto timelineLength = _getMaxDuration();

    auto timelineWidth = roundToInt (timelineLength * wPixPerSecond);
    auto timelineHeight = roundToInt (this->getNumTracks() * trackHeight * hPixPerSecond);
    auto heightBuffer = trackHeight * 3;
    this->setSize (timelineWidth, timelineHeight + heightBuffer);
}

//==================
int TimelineContent::getNumTracks() const
{
    return (int)this->_getTrackLanes().size();
}

//===================
int TimelineContent::_calculateWidth(float duration, double pixPerSecond)
{
    int width = roundToInt(duration * pixPerSecond);
    return width;
}

//===================
float TimelineContent::_getMaxDuration() const
{
    auto maxDur = 0.f;
    
    for(auto trackLane : this->_getTrackLanes())
    {
        if(trackLane->getDuration() > maxDur)
            maxDur = trackLane->getDuration();
    }
    
    return maxDur;
}

//===================
int TimelineContent::_calculateHeight(int numTracks)
{
    auto heightOfAllTracks = trackHeight * numTracks;
    auto extraVerticalSpace = trackHeight * 3; // at bottom of timeline there will be extra space
    auto newHeight = heightOfAllTracks + extraVerticalSpace;
    return newHeight;
}

//==================
juce::Array<TrackLane*> TimelineContent::_getTrackLanes() const
{
    juce::Array<TrackLane*> trackLanes;
    
    for (auto* component : this->getChildren())
    {
        auto trackLane = dynamic_cast<TrackLane*>(component);
        if(!trackLane)
            continue;
        
        trackLanes.add(trackLane);
    }
    
    return trackLanes;
    
}


