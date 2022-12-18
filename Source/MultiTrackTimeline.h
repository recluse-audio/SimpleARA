/*
  ==============================================================================

    MultiTrackTimeline.h
    Created: 15 Dec 2022 6:20:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class TrackLane;
class TimelineContent;
class TimelineViewport;
class OverlayComponent;
class ZoomControls;
class PlayHeadState;
class ZoomState;

//==============================================================================
/*
    Base class for a component that handles scrollable timelines
    This is essentially the editor mode of a DAW
*/
class MultiTrackTimeline  : public juce::Component
{
public:
    MultiTrackTimeline(PlayHeadState& pState);
    ~MultiTrackTimeline() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void addTrackLane(TrackLane* newTrackLane);
    void insertTrackLane(TrackLane* newTrackLane, int index);
    void removeTrackLane(TrackLane* trackLane);
    
    void zoom(float widthFactor, float heightFactor);
    void updateViewport();
	
	PlayHeadState& getPlayHeadState() const;
	ZoomState& getZoomState() const;
    
private:
    int viewportHeightOffset = 0;
    static constexpr auto minimumZoom = 10.0;
    static constexpr auto trackHeight = 60;
    double timelineLength = 0;
    double widthPixelPerSecond = minimumZoom * 4;
	double heightPixelPerSecond = minimumZoom;

    std::unique_ptr<TimelineContent> timelineContent;
    std::unique_ptr<TimelineViewport> timelineViewport;
    std::unique_ptr<OverlayComponent> overlay;
    std::unique_ptr<ZoomControls> zoomControls;
	
	std::unique_ptr<ZoomState> zoomState;

    PlayHeadState& playheadState;
    
	void _updateZoom();
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



