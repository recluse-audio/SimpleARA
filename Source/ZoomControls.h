/*
  ==============================================================================

    ZoomControls.h
    Created: 1 Nov 2022 12:48:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ZoomControls : public Component
{
public:
    ZoomControls()
    {
        addAndMakeVisible (zoomInButton);
        addAndMakeVisible (zoomOutButton);
    }

    void setZoomInCallback  (std::function<void()> cb)   { zoomInButton.onClick  = std::move (cb); }
    void setZoomOutCallback (std::function<void()> cb)   { zoomOutButton.onClick = std::move (cb); }

    void setVertical(bool orientVertically)
    {
        isVertical = orientVertically;
    }
    
    void resized() override
    {
        zoomInButton.setBoundsRelative(0.55f, 0.f, 0.35f, 1.f);
        zoomOutButton.setBoundsRelative(0.1, 0.f, 0.35f, 1.f);
    }

private:
    bool isVertical = false;
    TextButton zoomInButton { "+" }, zoomOutButton { "-" };
};
