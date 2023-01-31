/*
  ==============================================================================

    ARAView.h
    Created: 16 Jan 2023 3:29:22pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ZoomState.h"
#include "ARAViewSection.h"

//==============================================================================
/*
*/
class ARAView  : public juce::Component
{
public:
    ARAView(ARAViewSection& section) : araSection(section), zoomState(section.getZoomState())
    {

    }

    ~ARAView() override
    {
    }

	
	virtual void updateZoomState(const ZoomState& zoomState) = 0;


private:
	ZoomState& zoomState;
	ARAViewSection& araSection;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAView)
};
