/*
  ==============================================================================

    TimelineContent.cpp
    Created: 15 Dec 2022 7:29:07pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimelineContent.h"
#include "Track.h"
#include "MultiTrackTimeline.h"
#include "ZoomState.h"
#include "TimeRuler.h"
#include "TimeGrid.h"
#include "PlayheadMarker.h"

//==============================================================================
TimelineContent::TimelineContent(MultiTrackTimeline& timeLine)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
{
    timeRuler = std::make_unique<TimeRuler>(timeLine);
    addAndMakeVisible(timeRuler.get());

    timeGrid = std::make_unique<TimeGrid>(timeLine);
    timeGrid->setAlwaysOnTop(true);
    addAndMakeVisible(timeGrid.get());
    
    playheadMarker = std::make_unique<PlayheadMarker>();
    playheadMarker->setAlwaysOnTop(true);
    addAndMakeVisible(playheadMarker.get());
}

//===================
TimelineContent::~TimelineContent()
{
    timeRuler.release();
    timeGrid.release();
    playheadMarker.release();
    trackArray.clear();
}

//===================
void TimelineContent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::darkgrey);
    g.fillAll();
}

//===================
void TimelineContent::resized()
{
    auto bounds = this->getLocalBounds();
    
    timeRuler->setBounds(mTimeline.getTrackLabelWidth(), 0, this->getWidth(), 20);
    timeGrid->setBounds(mTimeline.getTrackLabelWidth(), 20, this->getWidth(), this->getHeight() - 20);

    for(auto track : trackArray)
    {
        auto yPos = track->getOrderIndex() * trackHeight;
        track->setBounds (0, yPos + 20, bounds.getWidth(), trackHeight);
        track->resized();
    }
	
    
//    for (auto* component : this->getChildren())
//    {
//        auto trackLane = dynamic_cast<TrackLane*>(component);
//        if(!trackLane)
//            continue;
//
//        auto yPos = trackLane->getOrderIndex() * trackHeight;
//        component->setBounds (0, yPos, bounds.getWidth(), trackHeight);
//        component->resized();
//    }

}

//====================
void TimelineContent::setTrackHeight(int newHeight)
{
    trackHeight = newHeight;
    resized();
}

//====================
void TimelineContent::updatePlayheadPosition(double currentPosInSeconds)
{
    auto proportionOfDuration = currentPosInSeconds / _getMaxDuration();
    playheadPositionInPixels = (this->getWidth() * proportionOfDuration) + mTimeline.getTrackLabelWidth();
    playheadMarker->setBounds(playheadPositionInPixels - 1, 0, 3, this->getHeight());
    //repaint();
}

//====================
void TimelineContent::updateZoomState()
{
    for(auto track : trackArray)
    {
        track->updateZoomState();
    }
    
	auto pixPerSecond = mTimeline.getZoomState().getPixelsPerSecond();
	auto timelineLength = _getMaxDuration();

	auto timelineWidth = roundToInt (timelineLength * pixPerSecond);
	auto timelineHeight = roundToInt (this->getNumTracks() * mTimeline.getZoomState().getTrackHeight());
	this->setSize (timelineWidth, timelineHeight );
}


//==================
double TimelineContent::getDurationInSeconds() const
{
    return _getMaxDuration();
}

//==================
int TimelineContent::getNumTracks() const
{
    return (int)trackArray.size();
}

//===================
int TimelineContent::_calculateWidth(float duration, double pixPerSecond)
{
    int width = roundToInt(duration * pixPerSecond);
    return width;
}

//===================
double TimelineContent::_getMaxDuration() const
{
    double maxDur = defaultDuration;
    
	
	
	if(trackArray.isEmpty())
		return maxDur;
	
    for(auto track : trackArray)
    {
        if(track->getDuration() > maxDur)
            maxDur = track->getDuration();
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
void TimelineContent::addTrackLane(int orderIndex)
{
    
    resized();
}


void TimelineContent::addTrackLane(Track* newTrack)
{
    trackArray.add(newTrack);
   // trackLanes.emplace_back(newLane);
    this->addAndMakeVisible(newTrack);
    resized();
}


