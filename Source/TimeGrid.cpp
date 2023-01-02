/*
  ==============================================================================

    TimeGrid.cpp
    Created: 22 Dec 2022 3:45:19pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeGrid.h"
#include "MultiTrackTimeline.h"
#include "ZoomState.h"
//==============================================================================
TimeGrid::TimeGrid(MultiTrackTimeline& timeLine) : mTimeline(timeLine)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TimeGrid::~TimeGrid()
{
}

void TimeGrid::paint (juce::Graphics& g)
{
    auto pixWidth = this->getWidth();
    auto pixPerSecond = mTimeline.getZoomState().getPixelsPerSecond();
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.2f));
    // One at zero and one at every second after
    int tickMarkPosition = 0;
    while( tickMarkPosition < pixWidth)
    {
        g.drawVerticalLine(tickMarkPosition, 0, this->getHeight());
        tickMarkPosition += pixPerSecond;
    }
}

void TimeGrid::resized()
{
    repaint();

}
