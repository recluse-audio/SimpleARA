/*
  ==============================================================================

    TrackRegion.cpp
    Created: 16 Dec 2022 6:15:52pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackRegion.h"
#include "MultiTrackTimeline.h"

//==============================================================================
TrackRegion::TrackRegion(MultiTrackTimeLine& timeLine, float startPos, float duration)
: MultiTrackObjectBase::MultiTrackObjectBase(timeLine)
{
    rangeInSeconds = std::make_unique<juce::Range<float>>(startPos, startPos +  duration);
	if(!rangeInSeconds->isEmpty())
		DBG(startPos);
}

TrackRegion::~TrackRegion()
{
}

void TrackRegion::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
}

void TrackRegion::resized()
{

}



//=======================
juce::Range<float>* TrackRegion::getRangeInSeconds() const
{
    return rangeInSeconds.get();
}

//=======================
void TrackRegion::updateZoomState()
{
	
}
