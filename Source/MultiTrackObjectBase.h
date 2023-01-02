/*
  ==============================================================================

    MultiTrackObjectBase.h
    Created: 18 Dec 2022 3:01:00pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MultiTrackTimeline;
/**
	Base class for the objects in a multi-track timeline
	Track Lane, Track Region, Headers, Overlays
 */
class MultiTrackObjectBase
{
public:
	MultiTrackObjectBase(MultiTrackTimeline& timeLine);
	MultiTrackObjectBase(MultiTrackTimeline& timeLine, int orderIndex);
	~MultiTrackObjectBase();
	
    /** Object will call this on its subcomponents (if any), then update its own size, which then calls 'resized()' where position of sub-objects will occur */
	virtual void updateZoomState() = 0;
	
	virtual void setOrderIndex(int newIndex);
	virtual int  getOrderIndex() const;
	

    
protected:
	MultiTrackTimeline& mTimeline;
	int orderIndex = -1;
};


