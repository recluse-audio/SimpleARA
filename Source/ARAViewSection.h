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
class SequenceHeaderContent;
class TimeRuler;
class ZoomState;
class PlayHeadState;
//==============================================================================
/*
    Currently trying method where entire document is plotted on region or sequence focus is accompolished simply by zooming the viewport the relevant area.  I don't think the invisible parts of a viewport are rendered so I think this is ok
*/
class ARAViewSection  : public juce::Component
, public juce::Timer
, public juce::ARADocument::Listener
{
public:
    ARAViewSection(SimpleARAEditor& mEditor);
    ~ARAViewSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    void timerCallback() override;

    void didAddRegionSequenceToDocument (juce::ARADocument* doc, juce::ARARegionSequence* sequence) override;
    
    // clears current 
    void rebuildFromDocument();
    // Sets which ARA view will be in focus
   // void setFocus(SimpleARAEditor::FocusView focus);
    void setDocumentFocus();
    void setSequenceFocus();
    void setRegionFocus();

    
    juce::ARADocument& getARADocument();
    ZoomState& getZoomState();
    SimpleARAEditor& getEditor();
    WaveformCache& getWaveCache();
private:
    
    SimpleARAEditor& mEditor;
    PlayHeadState& playheadState;
    
    std::unique_ptr<WaveformCache> waveCache;
    std::unique_ptr<ZoomState> zoomState;

//    std::unique_ptr<DocumentView> documentView;
    
    std::unique_ptr<juce::Viewport> headerViewport;
    std::unique_ptr<SequenceHeaderContent> headerContent;
    
    std::unique_ptr<juce::Viewport> documentViewport;
    std::unique_ptr<DocumentView> documentContent;
    
    std::unique_ptr<juce::Viewport> timeRulerViewport;
    std::unique_ptr<TimeRuler> timeRulerContent;
    
    void _initializeViews(juce::ARADocument* document);
    // Prepare the playback region to show 
    void _preparePlaybackRegionView(juce::ARADocument* document, int indexOfRegionToView);
    
    // updates zooms on this and all subcomponents according to this zoom state
    void _updateZoomState();
    
    
    void _addRegionSequence(juce::ARARegionSequence* sequence);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAViewSection)
};
