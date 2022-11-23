/*
  ==============================================================================

    GlobalDefines.h
    Created: 18 Nov 2022 1:16:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define HexStringForPointer( ptr ) juce::String::toHexString((unsigned long long)(void*)ptr)

static juce::int64 getAudioSourceStartInTimeLine(juce::ARAPlaybackRegion* playbackRegion)
{
	jassert(playbackRegion != nullptr);
	
	auto regionStartInTimeline = playbackRegion->getStartInPlaybackTime();
	auto regionStartInAudioMod = playbackRegion->getStartInAudioModificationTime();
	auto sourceStartInTimeline = regionStartInTimeline - regionStartInAudioMod;
	
	return sourceStartInTimeline;
}


