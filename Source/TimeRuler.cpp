/*
  ==============================================================================

    TimeRuler.cpp
    Created: 21 Dec 2022 2:26:06pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeRuler.h"
#include "MultiTrackTimeline.h"
#include "ZoomState.h"
//==============================================================================
TimeRuler::TimeRuler(ARAViewSection& section) : viewSection(section)
{

}

TimeRuler::~TimeRuler()
{
}

void TimeRuler::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);
    auto pixWidth = this->getWidth();
    auto pixPerSecond = viewSection.getZoomState().getPixelsPerSecond();
    
    g.setColour(juce::Colours::whitesmoke);
    // One at zero and one at every second after
    int tickMarkPosition = 0;
    float timePos = 0.f;
    while( tickMarkPosition < pixWidth)
    {
        g.drawVerticalLine(tickMarkPosition, 0, this->getHeight());
        g.drawText(juce::String(timePos), tickMarkPosition + 1, 0, 10, 7, juce::Justification::centredLeft);
        tickMarkPosition += pixPerSecond;
        timePos += 1.f;
        if(timePos > 10)
            DBG(timePos);
    }
    
}

void TimeRuler::resized()
{
    repaint();

}

//========================
void TimeRuler::updateZoomState()
{
    repaint();
}
