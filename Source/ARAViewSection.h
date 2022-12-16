/*
  ==============================================================================

    ARAViewSection.h
    Created: 2 Dec 2022 6:42:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SimpleARAEditor;
class DocumentView;
class PlaybackRegionView;
class WaveformCache;

//==============================================================================
/*
*/
class ARAViewSection  : public juce::Component
{
public:
    ARAViewSection(SimpleARAEditor& mEditor);
    ~ARAViewSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Sets which ARA view will be in focus
   // void setFocus(SimpleARAEditor::FocusView focus);
    void setDocumentFocus();
    void setSequenceFocus();
    void setRegionFocus();
    
private:
    SimpleARAEditor& mEditor;
    std::unique_ptr<DocumentView> documentView;
    std::unique_ptr<PlaybackRegionView> playbackRegionView;
    
    std::unique_ptr<WaveformCache> waveCache;
    
    void _initializeViews(juce::ARADocument* document);
    // Prepare the playback region to show 
    void _preparePlaybackRegionView(juce::ARADocument* document, int indexOfRegionToView);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAViewSection)
};
