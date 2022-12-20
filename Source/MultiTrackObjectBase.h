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
	
	virtual void updateZoomState() = 0;
	
	virtual void setOrderIndex(int newIndex);
	virtual int  getOrderIndex() const;
	

    
protected:
	MultiTrackTimeline& mTimeline;
	int orderIndex = -1;
	
    class ObjectKey
    {
    public:
        explicit ObjectKey (MultiTrackObjectBase* object, int index)
            : orderIndex (index), pObject (object)
        {
        }

        bool operator< (const ObjectKey& other) const
        {
            return std::tie (orderIndex, pObject) < std::tie (other.orderIndex, other.pObject);
        }

        ARA::ARAInt32 orderIndex;
        MultiTrackObjectBase* pObject;
    };
};


