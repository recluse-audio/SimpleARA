/*
  ==============================================================================

    ARA_RegionSequence.h
    Created: 16 Jan 2023 3:07:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RegionSequenceView;
class SequenceHeader;
/**
	Sub-class of ARA object.
	Sub-classed to add functionality used to keep track of associated view/header as well as return the end pos of
	the last region in its vector
*/
class ARA_RegionSequence : public juce::ARARegionSequence
{
public:
	using juce::ARARegionSequence::ARARegionSequence;
	
	// returns the playbacktime position of the end of the last region in this region sequence in seconds
	double getEndOfLastRegion() const;
	void setView(RegionSequenceView* view);
private:
	juce::WeakReference<RegionSequenceView> mView;
};
