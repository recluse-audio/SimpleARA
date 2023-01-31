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
class ZoomControls;
//==============================================================================
/*
    Currently trying method where entire document is plotted on region or sequence focus is accompolished simply by zooming the viewport the relevant area.  I don't think the invisible parts of a viewport are rendered so I think this is ok
*/
class ARAViewSection  : public juce::Component
, public juce::Timer
, public juce::ARADocument::Listener
, public juce::ScrollBar::Listener
{
public:
    ARAViewSection(SimpleARAEditor& mEditor);
    ~ARAViewSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    void timerCallback() override;

    void didAddRegionSequenceToDocument (juce::ARADocument* doc, juce::ARARegionSequence* sequence) override;
	void didEndEditing(juce::ARADocument* doc) override;
	
	void scrollBarMoved (juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart) override;


	
    // Sets which ARA view will be in focus
   // void setFocus(SimpleARAEditor::FocusView focus);
    void setDocumentFocus();
    void setSequenceFocus();
    void setRegionFocus();
	

	void setViewportTimeRange(double startInSeconds, double durationInSeconds);
	void setViewportEndPos(double endInSeconds);
	double getDuration() const;

    
    juce::ARADocument& getARADocument();
    ZoomState& getZoomState();
    SimpleARAEditor& getEditor();
    WaveformCache& getWaveCache();
	
private:
    SimpleARAEditor& mEditor;
    PlayHeadState& playheadState;
    
	juce::Range<double> viewportTimeRange;
	bool shouldUpdateViewport = false;
	int verticalScrollOffset = 0;
	int horizontalScrollOffset = 0;
	   
    std::unique_ptr<WaveformCache> waveCache;
    std::unique_ptr<ZoomState> zoomState;
    
    std::unique_ptr<juce::Viewport> headerViewport;
    std::unique_ptr<SequenceHeaderContent> headerContent;
    
    std::unique_ptr<juce::Viewport> documentViewport;
    std::unique_ptr<DocumentView> documentContent;
    
    std::unique_ptr<juce::Viewport> timeRulerViewport;
    std::unique_ptr<TimeRuler> timeRulerContent;
    
	std::unique_ptr<ZoomControls> zoomControls;
	std::unique_ptr<ZoomControls> vertZoomControls;

	//
    void _initializeViews(juce::ARADocument* document);
	
    // Prepare the playback region to show 
    void _preparePlaybackRegionView(juce::ARADocument* document, int indexOfRegionToView);
    
    // updates zooms on this and all subcomponents according to this zoom state
    void _updateZoomState();
    
	//
    void _addRegionSequence(juce::ARARegionSequence* sequence);
	
	//
	void _updateViewport();
	
	// clears current
	void _rebuildFromDocument();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAViewSection)
};
