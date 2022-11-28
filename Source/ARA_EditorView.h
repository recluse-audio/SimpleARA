/*
  ==============================================================================

    ARA_EditorView.h
    Created: 26 Nov 2022 1:25:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ARA_PlaybackRegion.h"

class ARA_EditorView : public juce::ARAEditorView
{
public:
    using juce::ARAEditorView::ARAEditorView;
    
    ~ARA_EditorView()
    {
        //const auto& playbackRegions = this->getPlaybackRegions<ARA_PlaybackRegion*>();
    }
};
