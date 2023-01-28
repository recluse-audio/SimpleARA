/*
  ==============================================================================

    TimeRuler.cpp
    Created: 21 Dec 2022 2:26:06pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeRuler.h"
#include "ZoomState.h"
//==============================================================================
TimeRuler::TimeRuler(ARAViewSection& section)
: viewSection(section)
, zoomState(section.getZoomState())
{
	zoomState.addChangeListener(this);
}

TimeRuler::~TimeRuler()
{
	zoomState.removeChangeListener(this);
}

void TimeRuler::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::orange);
    auto pixWidth = this->getWidth();
    
    g.setColour(juce::Colours::whitesmoke);
    // One at zero and one at every second after
    int tickMarkPosition = 0;
    float timePos = 0.f;
	
    while( tickMarkPosition < (float)pixWidth)
    {
		auto pixPerSecond = zoomState.getPixelsPerSecond();
		auto labelX = tickMarkPosition + 1;
		auto labelY = 0;
		auto labelWidth = pixPerSecond - 2;
		auto labelHeight = 7;
		auto labelText = juce::String(timePos, 2);
		
        g.drawVerticalLine(tickMarkPosition, 0, this->getHeight());
		
        g.drawText(labelText, labelX, labelY, labelWidth, labelHeight, juce::Justification::centredLeft);
		
		tickMarkPosition += zoomState.getPixelsPerSecond();
		
        timePos += 1.f;
//        if(timePos > 10)
//            DBG(timePos);
    }
    
}

void TimeRuler::resized()
{

}

void TimeRuler::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if(source == &zoomState)
	{
		updateZoomState();
	}
}


//========================
void TimeRuler::updateZoomState()
{
	auto width = viewSection.getDuration() * zoomState.getPixelsPerSecond();
	auto height = zoomState.getTrackHeight();
	this->setSize(width, height);
}
