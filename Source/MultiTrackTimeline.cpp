/*
  ==============================================================================

    MultiTrackTimeline.cpp
    Created: 15 Dec 2022 6:20:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MultiTrackTimeline.h"
#include "TimelineContent.h"
#include "TimelineViewport.h"
#include "TimeRuler.h"
#include "Track.h"
#include "ZoomControls.h"
#include "UtilObjects.h"
#include "ZoomState.h"
#include "PlayHeadOverlay.h"

//==============================================================================
MultiTrackTimeline::MultiTrackTimeline(PlayHeadState& pState) : playheadState(pState)
{
    timeRulerContent = std::make_unique<TimeRuler>(*this);
    timeRulerViewport = std::make_unique<TimelineViewport>();
    timeRulerViewport->setViewedComponent(timeRulerContent.get());
    addAndMakeVisible(timeRulerViewport.get());
    
    timelineContent = std::make_unique<TimelineContent>(*this);

    timelineViewport = std::make_unique<TimelineViewport>();
    timelineViewport->onVisibleAreaChanged = [this] (const auto& r)
    {
       // verticalScrollOffset = r.getY();
        resized();
    };
    
    timelineViewport->setViewedComponent(timelineContent.get());
    addAndMakeVisible(timelineViewport.get());


	zoomControls = std::make_unique<ZoomControls>();
	zoomControls->setZoomInCallback  ([this] { zoom (1.25, 1.0); });
	zoomControls->setZoomOutCallback ([this] { zoom (0.75, 1.0); });
	addAndMakeVisible (zoomControls.get());
	
	
	zoomState = std::make_unique<ZoomState>();
    
    for(int i = 0; i < 15; i++)
    {
        timelineContent->addTrackLane(new Track(*this, i));

    }
	
    setSize(300, 300);

	/** TO DO: This has to happen after */
    this->_updateZoomStates();
    this->setViewportTimeRange(10.0, 2.0); // first 10 seconds
    this->startTimerHz(30);
    

}

MultiTrackTimeline::~MultiTrackTimeline()
{
    timelineContent.reset();
    timelineViewport.reset();
}

void MultiTrackTimeline::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkred.darker());
}

void MultiTrackTimeline::resized()
{
    auto bounds = this->getLocalBounds();
    int trackHeaderWidth = zoomState->getHeaderWidth();
    
    timeRulerViewport->setBounds(trackHeaderWidth, 0, bounds.getWidth() - trackHeaderWidth, 30 );
    
    timelineViewport->setBounds(0, 30, bounds.getWidth(), bounds.getHeight() - 30);
 	//playheadOverlay->setBounds(trackLabelWidth, 0, bounds.getWidth() - trackLabelWidth, bounds.getHeight());
	zoomControls->setBoundsRelative(0.85f, 0.8f, 0.1f, 0.1f);

}

//====================
void MultiTrackTimeline::addTrackLane(int index)
{
    timelineContent->addTrackLane(index);
    resized();
}


//====================
void MultiTrackTimeline::zoom(float widthFactor, float heightFactor)
{
	zoomState->increaseHorizontalZoom(widthFactor);
	_updateZoomStates();
}


//===================
void MultiTrackTimeline::_updateZoomStates()
{
	timelineContent->updateZoomState();
    timeRulerContent->updateZoomState();
}

//===================
PlayHeadState& MultiTrackTimeline::getPlayHeadState() const
{
	return playheadState;
}

//===================
ZoomState& MultiTrackTimeline::getZoomState() const
{
	return *zoomState.get();
}

//===================
int MultiTrackTimeline::getTrackLabelWidth() const
{
    return trackLabelWidth;
}

//===================
void MultiTrackTimeline::timerCallback()
{
    if(shouldUpdateViewport)
        _updateViewport();
    
    if(playheadState.isPlaying)
    {
        timelineContent->updatePlayheadPosition(playheadState.timeInSeconds);
        
        if(playheadState.timeInSeconds > viewPortTimeRange.getEnd())
            setViewportEndPos(playheadState.timeInSeconds);
        
    }
}

//===================
void MultiTrackTimeline::setViewportTimeRange(double startInSeconds, double durationInSeconds)
{
    // This will adjust how much of the timeline is visible at a given moment
    // This adjusts the pixPerSecond so do this first
    zoomState->zoomToShowDuration(this->getWidth(), durationInSeconds);
    viewPortTimeRange.setStart(startInSeconds);
    viewPortTimeRange.setEnd(startInSeconds + durationInSeconds);
    shouldUpdateViewport = true;
}

//==================
void MultiTrackTimeline::setViewportEndPos(double endInSeconds)
{
    viewPortTimeRange = viewPortTimeRange.movedToEndAt(endInSeconds);
    shouldUpdateViewport = true;
}

void MultiTrackTimeline::_updateViewport()
{
    auto proportionX = viewPortTimeRange.getStart() / timelineContent->getDurationInSeconds();
    auto xPositionInContent = timelineContent->getWidth() * proportionX;
    timelineViewport->setViewPosition(xPositionInContent, verticalScrollOffset);
    timeRulerViewport->setViewPosition(xPositionInContent, 0);
    shouldUpdateViewport = false;
}


double MultiTrackTimeline::getDuration() const
{
    return timelineContent->getDurationInSeconds();
}
