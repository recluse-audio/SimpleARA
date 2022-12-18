/*
  ==============================================================================

    MultiTrackObjectBase.h
    Created: 18 Dec 2022 3:01:00pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MultiTrackTimeLine;
/**
	Base class for the objects in a multi-track timeline
	Track Lane, Track Region, Headers, Overlays
 */
class MultiTrackObjectBase
{
public:
	MultiTrackObjectBase(MultiTrackTimeLine& timeLine);
	~MultiTrackObjectBase();
	
	virtual void updateZoomState() = 0;
	
	virtual void setTimeLine(MultiTrackTimeLine* newTimeLine);
	
protected:
	MultiTrackTimeLine& mTimeLine;
	
};

