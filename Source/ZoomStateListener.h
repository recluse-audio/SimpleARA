/*
  ==============================================================================

    ZoomStateListener.h
    Created: 31 Jan 2023 5:00:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ZoomState.h"

class ZoomStateListener : public juce::ChangeListener
{
public:
	ZoomStateListener(ZoomState& state) : zoomState(state)
	{
		zoomState.addChangeListener(this);
	}
	
	~ZoomStateListener()
	{
		zoomState.removeChangeListener(this);
	}
	
	void changeListenerCallback(juce::ChangeBroadcaster* source) override
	{
		if(source == &zoomState)
			updateZoomState();
	}
	
	virtual void updateZoomState() = 0;
	
	ZoomState& getZoomState() const
	{
		return zoomState;
	}
	
private:
	ZoomState& zoomState;
	
	
};
