/*
  ==============================================================================

    ARA_PlaybackRegion.cpp
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_PlaybackRegion.h"
#include "PlaybackRegionView.h"




void ARA_PlaybackRegion::setCurrentlyInView(bool inView)
{
    currentlyInView = inView;
}

bool ARA_PlaybackRegion::isCurrentlyInView() const
{
    return currentlyInView;
}

void ARA_PlaybackRegion::setCurrentlySelected(bool isSelected)
{
	currentlySelected = isSelected;
}

bool ARA_PlaybackRegion::isCurrentlySelected() const
{
	return currentlySelected;
}

juce::Range<double> ARA_PlaybackRegion::getFullRegionTimeRange()
{
	auto start = this->getStartInPlaybackTime() - this->getStartInAudioModificationTime();
	auto addThisToEndOfRegion = this->getAudioSourceDuration() - this->getEndInAudioModificationTime();
	auto end = this->getEndInPlaybackTime() + addThisToEndOfRegion;
	return juce::Range<double>(start, end);
	
}


juce::Range<int64> ARA_PlaybackRegion::getRangeToReadInAudioSource(juce::Range<int64> blockRange)
{
	jassert(mSampleRate > 0);
	
	auto readRange = _getRangeOverlappingRegion(blockRange);
	
	if(readRange.isEmpty())
		return readRange; // save the calculation if
	
	readRange = _getRangeOverlappingAudioSource(readRange);
	
	return readRange;
}


juce::int64 ARA_PlaybackRegion::getModOffset() const
{
	jassert(mSampleRate > 0);
	juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
	juce::Range<int64> modRange { getStartInAudioModificationSamples(), getEndInAudioModificationSamples() };
	
	const auto modOffset = getStartInAudioModificationSamples() - getStartInPlaybackSamples(mSampleRate);
	
	return modOffset;
}



void ARA_PlaybackRegion::setSampleRate(double sampleRate)
{
	mSampleRate = sampleRate;
}




double ARA_PlaybackRegion::getAudioSourceDuration() const
{
	return this->getAudioModification()->getAudioSource()->getDuration();
}



juce::Range<int64> ARA_PlaybackRegion::_getRangeOverlappingRegion(juce::Range<int64> blockRange)
{
	jassert(mSampleRate > 0);
	juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
	
	blockRange = blockRange.getIntersectionWith (regionRange);
	
	return blockRange;
}


juce::Range<int64> ARA_PlaybackRegion::_getRangeOverlappingAudioSource(juce::Range<int64> blockRange)
{
	jassert(mSampleRate > 0);
	juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
	juce::Range<int64> modRange { getStartInAudioModificationSamples(), getEndInAudioModificationSamples() };
	
	blockRange = blockRange.getIntersectionWith (modRange.movedToStartAt (regionRange.getStart()));
	
	return blockRange;
}
