/*
  ==============================================================================

    TrackHeaderContent.cpp
    Created: 2 Jan 2023 11:03:50am
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackHeaderContent.h"
#include "MultiTrackTimeline.h"
#include "TrackHeader.h"

//==============================================================================
TrackHeaderContent::TrackHeaderContent(MultiTrackTimeline& timeLine)
: MultiTrackObjectBase(timeLine)
{

}

TrackHeaderContent::~TrackHeaderContent()
{
    trackHeaders.clear();
}

void TrackHeaderContent::paint (juce::Graphics& g)
{

}

void TrackHeaderContent::resized()
{
    
}

void TrackHeaderContent::updateZoomState() override
{
    
}
