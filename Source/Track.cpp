/*
  ==============================================================================

    Track.cpp
    Created: 23 Dec 2022 10:27:54am
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Track.h"
#include "TrackLane.h"
#include "TrackHeader.h"
#include "ZoomState.h"

//==============================================================================
Track::Track()
{
    trackHeader = std::make_unique<TrackHeader>(timeLine);
    addAndMakeVisible(trackHeader.get());
    
    trackLane = std::make_unique<TrackLane>(timeLine);
    addAndMakeVisible(trackLane.get());
    
}


Track::~Track()
{
    trackHeader.reset();
    trackLane.reset();
}

void Track::paint (juce::Graphics& g)
{

}

void Track::resized()
{
    trackHeader->setTopLeftPosition(0, 0);
    trackLane->setTopLeftPosition(trackHeader->getRight() + 1, 0); // drawn at right edge of trackHeader
}

void Track::updateZoomState(ZoomState& zoomState)
{
    trackHeader->updateZoomState();
    trackLane->updateZoomState();
    
    int newWidth = trackHeader->getWidth() + trackLane->getWidth();
    int newHeight = mTimeline.getZoomState().getTrackHeight();
    this->setSize(newWidth, newHeight);
}


void Track::setTrackName(juce::StringRef newName)
{
    trackHeader->setName(newName);
}

double Track::getDuration() const
{
    return trackLane->getDuration();
}
