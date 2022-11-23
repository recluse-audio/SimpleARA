/*
  ==============================================================================

    VerticalLayoutViewportContent.h
    Created: 1 Nov 2022 12:49:44pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
constexpr auto trackHeight = 60;

class VerticalLayoutViewportContent : public Component
{
public:
	VerticalLayoutViewportContent()
	{
		
	}
	
    void resized() override
    {
        auto bounds = getLocalBounds();

        for (auto* component : getChildren())
        {
            component->setBounds (bounds.removeFromTop (trackHeight));
            component->resized();
        }
    }

    void setOverlayComponent (Component* component)
    {
        if (overlayComponent != nullptr && overlayComponent != component)
            removeChildComponent (overlayComponent);

        addChildComponent (component);
        overlayComponent = component;
    }

private:
    Component* overlayComponent = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalLayoutViewportContent)
};
