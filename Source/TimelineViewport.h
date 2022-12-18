/*
  ==============================================================================

    TimelineViewport.h
    Created: 15 Dec 2022 6:59:43pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TimelineViewport : public juce::Viewport
{
public:
    TimelineViewport()
    {
        
    }
    ~TimelineViewport()
    {
        
    }
    std::function<void (Rectangle<int>)> onVisibleAreaChanged;

private:
    void visibleAreaChanged (const Rectangle<int>& newVisibleArea) override
    {
        NullCheckedInvocation::invoke (onVisibleAreaChanged, newVisibleArea);
    }
    
    
};
