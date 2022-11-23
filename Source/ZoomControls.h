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

    void resized() override
    {
        FlexBox fb;
        fb.justifyContent = FlexBox::JustifyContent::flexEnd;

        for (auto* button : { &zoomInButton, &zoomOutButton })
            fb.items.add (FlexItem (*button).withMinHeight (30.0f).withMinWidth (30.0f).withMargin ({ 5, 5, 5, 0 }));

        fb.performLayout (getLocalBounds());
    }

private:
    TextButton zoomInButton { "+" }, zoomOutButton { "-" };
};
