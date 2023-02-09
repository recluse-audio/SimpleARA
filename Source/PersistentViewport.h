/*
  ==============================================================================

    PersistentViewport.h
    Created: 6 Feb 2023 6:06:23pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ZoomStateListener.h"

class ARAViewSection;


//==============================================================================
/*
	This class is a viewport that keeps track of its view position and maintains it when its child component is resized (via zooming)
*/
class PersistentViewport  : public juce::Viewport
, public ZoomStateListener
{
public:
	PersistentViewport(juce::StringRef name, ZoomState& zState) : ZoomStateListener(zState), juce::Viewport(name)

	void visibleAreaChanged (const Rectangle<int>& newVisibleArea) override
	{
		DBG("changed");
	}
	
	void updateZoomState() override
	{
		DBG("updateZoomt");
	}

	

private:
	// store relative values
	float relativeX = 0.f, relativeY = 0.f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PersistentViewport)
};
