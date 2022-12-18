/*
  ==============================================================================

    TimelineContent.h
    Created: 15 Dec 2022 7:29:07pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class TrackLane;
class TrackID;
//==============================================================================
/**
    This is basically a big rectangle with track lanes 
*/
class TimelineContent  : public juce::Component
{
public:
    TimelineContent();
    ~TimelineContent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setTrackHeight(int newHeight);
    void addTrackLane(TrackLane* newTrackLane);
    
    // Updates sizes of this and subcomponents based on new pixel per second zoom level
    void updateZoomLevel(double wPixPerSecond, double hPixPerSecond);
    int getNumTracks() const;
    
protected:
    int trackHeight = 60;
    
    // Returns the duration of the longest track. i.e. how long this timeline is plus some buffer
    float _getMaxDuration() const;
    // Converting the duration of the timeline into pixels at current zoom level
    int _calculateWidth(float duration, double pixPerSecond);
    // adjusts height of this component based on the tracks attached to it
    int _calculateHeight(int numTracks);
    //
    juce::Array<TrackLane*> _getTrackLanes() const;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineContent)
};