/*
  ==============================================================================

    TimeRuler.h
    Created: 21 Dec 2022 2:26:06pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ARAViewSection.h"
//==============================================================================
/*
*/
class TimeRuler  : public juce::Component
, public juce::ChangeListener
{
public:
    TimeRuler(ARAViewSection& section);
    ~TimeRuler() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	
	void updateZoomState();
    
private:
    ARAViewSection& viewSection;
	ZoomState& zoomState;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeRuler)
};
