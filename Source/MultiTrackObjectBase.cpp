/*
  ==============================================================================

    MultiTrackObjectBase.cpp
    Created: 18 Dec 2022 3:01:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "MultiTrackObjectBase.h"
#include "MultiTrackTimeline.h"

//===================
MultiTrackObjectBase::MultiTrackObjectBase(MultiTrackTimeline& timeLine) : mTimeline(timeLine)
{
}

//===================
MultiTrackObjectBase::MultiTrackObjectBase(MultiTrackTimeline& timeLine, int newIndex) : mTimeline(timeLine), orderIndex(newIndex)
{
}

//===================
MultiTrackObjectBase::~MultiTrackObjectBase()
{
	
}

//===================
void MultiTrackObjectBase::setOrderIndex(int newIndex)
{
	orderIndex = newIndex;
	
}

//===================
int MultiTrackObjectBase::getOrderIndex() const
{
	return orderIndex;
	
}

