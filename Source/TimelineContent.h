/*
  ==============================================================================

    TimelineContent.h
    Created: 15 Dec 2022 7:29:07pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultiTrackObjectBase.h"
class Track;
class TrackID;
class MultiTrackTimeline;
class TimeRuler;
class TimeGrid;
class PlayheadMarker;
//==============================================================================
/**
    This is basically a big rectangle with track lanes 
*/
class TimelineContent : public juce::Component,
						public MultiTrackObjectBase
{
public:
    TimelineContent(MultiTrackTimeline&);
    ~TimelineContent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setTrackHeight(int newHeight);
    void addTrackLane(int orderIndex); // overload this for ARA, pass it a playback region?
    void addTrackLane(Track* newLane);
    
	void updateZoomState() override;
    void updatePlayheadPosition(double newPosition);
    void setTrackHeaderWidth(int newWidth);

    int getNumTracks() const;
    
    // returns duration of longest track lane.  
    double getDurationInSeconds() const;
    
protected:	
    int trackHeight = 60;
	double defaultDuration = 120.0;
    double currentDuration = 0.0;
    int playheadPositionInPixels = 0;
    
    
    juce::OwnedArray<Track> trackArray;
    
    std::unique_ptr<TimeRuler> timeRuler;
    std::unique_ptr<TimeGrid> timeGrid;
    std::unique_ptr<PlayheadMarker> playheadMarker;
    
    // Returns the duration of the longest track. i.e. how long this timeline is plus some buffer
    double _getMaxDuration() const;
    // Converting the duration of the timeline into pixels at current zoom level
    int _calculateWidth(float duration, double pixPerSecond);
    // adjusts height of this component based on the tracks attached to it
    int _calculateHeight(int numTracks);
    //
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineContent)
};
