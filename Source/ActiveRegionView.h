/*
  ==============================================================================

    ActiveRegionView.h
    Created: 20 Nov 2022 5:21:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformCache;
class PlaybackRegionView;
class ARAViewSection;
class ARA_PlaybackRegion;

//==============================================================================
/**
	This class represents the Playback Region that is only the duration as it appears on the timeline
	
	see PlaybackRegionView
*/
class ActiveRegionView  : public juce::Component
, public juce::ARAEditorView::Listener
{
public:
    ActiveRegionView(ARAViewSection& section, ARA_PlaybackRegion& region);
    ~ActiveRegionView() override;
	
    void paint (juce::Graphics&) override;
    void resized() override;
	
	void mouseEnter(const juce::MouseEvent& e) override;
	void mouseExit(const juce::MouseEvent& e) override;
	void mouseDown(const juce::MouseEvent& e) override;
	
	
private:
	ARA_PlaybackRegion& playbackRegion;
	WaveformCache& waveCache;
    ARAViewSection& araSection;
    
	void _drawPlaybackRegion(juce::Graphics& g);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ActiveRegionView)
};
