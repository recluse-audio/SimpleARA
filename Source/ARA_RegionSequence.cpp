/*
  ==============================================================================

    ARA_RegionSequence.cpp
    Created: 16 Jan 2023 3:07:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_RegionSequence.h"
#include "RegionSequenceView.h"
#include "SequenceHeader.h"

double ARA_RegionSequence::getEndPositionInSeconds() const
{
	double endPos = 0.0;
	auto regions = this->getPlaybackRegions();
	for(auto region : regions)
	{
		auto regionEnd = region->getEndInPlaybackTime();
		if(regionEnd > endPos)
			endPos = regionEnd;
	}
	return endPos;
}

//==================
void ARA_RegionSequence::setView(RegionSequenceView *view)
{
	mView = view;
}
