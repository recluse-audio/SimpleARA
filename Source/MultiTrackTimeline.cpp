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
#include "TrackLane.h"
#include "ZoomControls.h"
#include "OverlayComponent.h"
#include "UtilObjects.h"
#include "ZoomState.h"

//==============================================================================
MultiTrackTimeline::MultiTrackTimeline(PlayHeadState& pState) : playheadState(pState)
{

    
    timelineContent = std::make_unique<TimelineContent>(this);

    timelineViewport = std::make_unique<TimelineViewport>();
    timelineViewport->onVisibleAreaChanged = [this] (const auto& r)
    {
        viewportHeightOffset = r.getY();
        overlay->setHorizontalOffset (r.getX());
        resized();
    };
    
    timelineViewport->setViewedComponent(timelineContent.get());
    addAndMakeVisible(timelineViewport.get());
    
	overlay = std::make_unique<OverlayComponent>(this);
	overlay->setZoomLevel (widthPixelPerSecond);
	addAndMakeVisible (overlay.get());

	zoomControls = std::make_unique<ZoomControls>();
	zoomControls->setZoomInCallback  ([this] { zoom (2.0, 1.0); });
	zoomControls->setZoomOutCallback ([this] { zoom (0.5, 1.0); });
	addAndMakeVisible (zoomControls.get());
	
    setSize(300, 300);
	
	zoomState = std::make_unique<ZoomState>();
    
    for(int i = 0; i < 12; i++)
    {
        addTrackLane(new TrackLane(this, i));

    }
	
	/** TO DO: This has to happen after */
	this->zoom(0.5f, 1.5f);

}

MultiTrackTimeline::~MultiTrackTimeline()
{
}

void MultiTrackTimeline::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkred.darker());
}

void MultiTrackTimeline::resized()
{
    timelineViewport->setBounds(getLocalBounds());
 	overlay->setBounds(getLocalBounds());
	zoomControls->setBoundsRelative(0.9f, 0.8f, 0.05f, 0.1f);

}

//====================
void MultiTrackTimeline::addTrackLane(TrackLane *newTrackLane)
{
    timelineContent->addAndMakeVisible(newTrackLane);
    updateViewport();
}


//====================
void MultiTrackTimeline::zoom(float widthFactor, float heightFactor)
{
	zoomState->setHorizontalZoom(widthFactor);
	_updateZoom();
}

//====================
void MultiTrackTimeline::_updatePixelsPerSecond(double wPixPerSecond, double hPixPerSecond)
{
    overlay->setZoomLevel(wPixPerSecond);
    timelineContent->updateZoomLevel(wPixPerSecond, hPixPerSecond);
}

//===================
void MultiTrackTimeline::updateViewport()
{
    timelineLength = 120.0;

    timelineContent->resized();

    resized();
}

//===================
void MultiTrackTimeline::_updateZoom()
{
	
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
