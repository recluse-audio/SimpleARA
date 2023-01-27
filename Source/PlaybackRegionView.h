/*
  ==============================================================================

    PlaybackRegionView.h
    Created: 1 Nov 2022 12:47:47pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveformCache.h"
#include "ARAViewSection.h"

class ActiveRegionView;
class AudioModView;
class AudioSourceView;
class SimpleARAEditor;
class ARA_PlaybackRegion;

//==============================================================================
/**
 Representation of a PlaybackRegion and its AudioMod / AudioSource
	This class contains three layers of views representing the ARA hierarchy of a given PlaybackRegion
 
	AudioSourceView - A thumbnail of the full AudioSource
	AudioModView - Shows shared data between mutually dependent regions, ( right now just color )
	ActiveRegionView - Actual portion of Audio Source in Playback Region after user trimming / edits
 
	Interesting Note:  The ActiveRegionView represents the portion of the AudioSource and DAW timeline that the 	PlaybackRenderer::processBlock() is called during
	
*/
class PlaybackRegionView : public juce::Component
, private juce::ARAPlaybackRegion::Listener
, public juce::ChangeListener
{
public:
	PlaybackRegionView (ARAViewSection& section, ARA_PlaybackRegion& region);

	~PlaybackRegionView() override;


	void paint (juce::Graphics& g) override;

	void resized() override;
	
	void didUpdatePlaybackRegionProperties (ARAPlaybackRegion*) override;

	
	void mouseEnter(const juce::MouseEvent& e) override;
	void mouseExit(const juce::MouseEvent& e) override;
	void mouseDown(const juce::MouseEvent& e) override;


	void updateGlobalAddressLabel();
	void resetGlobalAddressLabel();
	
    void updateZoomState();

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	
	/** Time range for the playback region in the DAWs timeline, but only the active portion of the region*/
	juce::Range<double> getActiveRegionTimeRange() const;

	/**
	 Time range for the playback region in the DAWs timeline if it were the full length of the audio source
		Note: this can hypothetically return a negative start position if the full audio source would extend to before DAW position 0
		Some hosts may even allow the active regions to exist at a negative time position.
		--Joys of ARA baby
	 */
	juce::Range<double> getFullRegionTimeRange() const;

private:
    ARA_PlaybackRegion& playbackRegion;
    ARAViewSection& araSection;
	ZoomState& zoomState;
    
	std::unique_ptr<ActiveRegionView> activeRegionView;
	std::unique_ptr<AudioModView> audioModView;
	std::unique_ptr<AudioSourceView> audioSourceView;
    
    std::unique_ptr<juce::Slider> slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
	
	void _updateRegionBounds();
	juce::StringRef _getARAObjectAddressStrings();
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackRegionView);
};
