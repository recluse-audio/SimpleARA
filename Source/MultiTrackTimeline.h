/*
  ==============================================================================

    MultiTrackTimeline.h
    Created: 15 Dec 2022 6:20:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ZoomState.h"

class TrackLane;
class TimeRuler;
class TimelineContent;
class TimelineViewport;
class TransportOverlay;
class ZoomControls;
class PlayHeadState;
class PlayHeadOverlay;

//==============================================================================
/*
    Base class for a component that handles scrollable timelines
    This is essentially the editor mode of a DAW
*/
class MultiTrackTimeline  : public juce::Component,
                            public juce::Timer
{
public:
    MultiTrackTimeline(PlayHeadState& pState);
    ~MultiTrackTimeline() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void addTrackLane(int index);
    void removeTrackLane(int index);
    
    void zoom(float widthFactor, float heightFactor);
    //
    void setViewportEndPos(double endInSeconds);
    // This changes start position and affects zoom level
    void setViewportTimeRange(double startInSeconds, double durationInSeconds);
	
	PlayHeadState& getPlayHeadState() const;
	ZoomState& getZoomState() const;
    int getTrackLabelWidth() const;
    void timerCallback() override;
    double getDuration() const;
    
private:
    int verticalScrollOffset = 0;
    static constexpr auto minimumZoom = 10.0;
    static constexpr auto trackHeight = 60;
    static constexpr auto trackLabelWidth = 80;
    double timelineLength = 0;
    double widthPixelPerSecond = minimumZoom * 4;
	double heightPixelPerSecond = minimumZoom;
    
    juce::Range<double> viewPortTimeRange;
    bool shouldUpdateViewport = false;

    std::unique_ptr<TimeRuler> timeRulerContent;
    std::unique_ptr<juce::Viewport> timeRulerViewport;
    
    std::unique_ptr<juce::Viewport> trackHeaderViewport;
    
    std::unique_ptr<TimelineContent> timelineContent;
    std::unique_ptr<TimelineViewport> timelineViewport;
    //std::unique_ptr<PlayHeadOverlay> playheadOverlay;
    std::unique_ptr<ZoomControls> zoomControls;
	
	std::unique_ptr<ZoomState> zoomState;

    PlayHeadState& playheadState;
    
    void _updateViewport();

    // Using our playhead state we will update the stored playhead position data and the 
    void _updatePlayheadPosition();
    //
	void _updateZoomStates();
    // Called from zoom() this sets the zoom level of the timelineContent
    void _updatePixelsPerSecond(double widthPixPerSec, double heightPixPerSecond);
    
    // Returns the duration of the longest track. i.e. how long this timeline is plus some buffer
    float _getMaxTrackDuration() const;
    // Converting the duration of the timeline into pixels at current zoom level
    int _calculateViewportContentWidth(float duration, double pixPerSecond);
    // adjusts height of this component based on the tracks attached to it
    int _calculateViewportContentHeight(int numTracks);

    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiTrackTimeline)
};



