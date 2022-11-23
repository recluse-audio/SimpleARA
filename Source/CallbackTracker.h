/*
  ==============================================================================

    CallbackTracker.h
    Created: 21 Nov 2022 7:05:51pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CallbackTracker : private juce::ARADocument::Listener
, private juce::ARAPlaybackRegionListener
{
public:
	CallbackTracker();
	~CallbackTracker();
	
	// Iterates through all the listener callbacks that happened between willEndEditing() and didEndEditing()
	juce::StringRef getTextFromCallbacks();
	
	void willBeginEditing(juce::ARADocument*) override;
	void didEndEditing(juce::ARADocument*) override;
	void didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion*) override;
private:
	juce::StringArray callbacks;
};
