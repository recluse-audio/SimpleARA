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

//==============================================================================
MultiTrackTimeline::MultiTrackTimeline(PlayHeadState& pState) : playheadState(pState)
{
    overlay = std::make_unique<OverlayComponent>(playheadState);
    overlay->setZoomLevel (zoomLevelPixelPerSecond);
    addAndMakeVisible (overlay.get());

    zoomControls = std::make_unique<ZoomControls>();
    zoomControls->setZoomInCallback  ([this] { zoom (2.0); });
    zoomControls->setZoomOutCallback ([this] { zoom (0.5); });
    addAndMakeVisible (zoomControls.get());
    this->zoom(0.5f);
    
    timelineContent = std::make_unique<TimelineContent>();

    timelineViewport = std::make_unique<TimelineViewport>();
    timelineViewport->onVisibleAreaChanged = [this] (const auto& r)
    {
        viewportHeightOffset = r.getY();
        overlay->setHorizontalOffset (r.getX());
        resized();
    };
    
    timelineViewport->setViewedComponent(timelineContent.get());
    addAndMakeVisible(timelineViewport.get());
    
    setSize(300, 300);
    
    for(int i = 0; i < 12; i++)
    {
        addTrackLane(new TrackLane(i));

    }
    
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
    widthPixelPerSecond = jlimit (minimumZoom, minimumZoom * 32, widthPixelPerSecond * widthFactor);
    
    this->_updatePixelsPerSecond (widthPixelPerSecond, 1.f);
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



