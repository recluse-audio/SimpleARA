/*
  ==============================================================================

    CallbackTracker.cpp
    Created: 21 Nov 2022 7:05:51pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "CallbackTracker.h"
#include "GlobalDefines.h"

CallbackTracker::CallbackTracker()
{
	
}

CallbackTracker::~CallbackTracker()
{
	
}

juce::StringRef CallbackTracker::getTextFromCallbacks()
{
	juce::String fullText = {""};
	
	for(auto callbackText : callbacks)
	{
		fullText = fullText + callbackText + "\n";
	}
}

void CallbackTracker::willBeginEditing(juce::ARADocument* pDocument)
{
	auto callbackString = juce::String("willBeginEditing();");
	callbacks.add("ARA Document: " + HexStringForPointer(pDocument) + "called " + callbackString);
}

void CallbackTracker::didEndEditing(juce::ARADocument* pDocument)
{
	auto callbackString = juce::String("didEndEditing();");
	callbacks.add("ARA Document: " + HexStringForPointer(pDocument) + "called " + callbackString);
}

void CallbackTracker::didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion* pRegion)
{
	auto callbackString = juce::String("didUpdatePlaybackRegionProperties();");
	callbacks.add("ARA Playback Region: " + HexStringForPointer(pRegion) + "called " + callbackString);
}
