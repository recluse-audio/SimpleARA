/*
  ==============================================================================

    VerticalLayoutViewport.h
    Created: 1 Nov 2022 12:50:03pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VerticalLayoutViewportContent.h"
//==============================================================================
/*
*/
class VerticalLayoutViewport : public Viewport
{
public:
    VerticalLayoutViewport()
    {
        setViewedComponent (&content, false);
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId).brighter());
    }

    std::function<void (Rectangle<int>)> onVisibleAreaChanged;

    VerticalLayoutViewportContent content;

private:
    void visibleAreaChanged (const Rectangle<int>& newVisibleArea) override
    {
        NullCheckedInvocation::invoke (onVisibleAreaChanged, newVisibleArea);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalLayoutViewport)
};
