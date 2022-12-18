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
MultiTrackObjectBase::MultiTrackObjectBase()
{
	
}

//===================
MultiTrackObjectBase::MultiTrackObjectBase(MultiTrackTimeLine* timeLine)
{
	mTimeLine = timeLine;
}

//===================
MultiTrackObjectBase::~MultiTrackObjectBase()
{
	
}

//===================
void MultiTrackObjectBase::setTimeLine(MultiTrackTimeLine *newTimeLine)
{
	mTimeLine = newTimeLine;
}
