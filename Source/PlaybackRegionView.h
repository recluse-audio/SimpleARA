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

class ActiveRegionView;
class AudioModView;
class AudioSourceView;

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
, public juce::ChangeListener
, public juce::ARAPlaybackRegion::Listener
{
public:
	PlaybackRegionView (juce::ARAPlaybackRegion& region, WaveformCache& cache);

	~PlaybackRegionView() override;

	void changeListenerCallback (juce::ChangeBroadcaster*) override;

	void paint (juce::Graphics& g) override;

	void resized() override;
	
	void willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* playbackRegion, ARA::PlugIn::PropertiesPtr<ARA::ARAPlaybackRegionProperties> newProperties) override;
	void didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion* playbackRegion) override;
	void didUpdatePlaybackRegionContent (juce::ARAPlaybackRegion* playbackRegion, ARAContentUpdateScopes scopeFlags) override;
	void willDestroyPlaybackRegion (juce::ARAPlaybackRegion* playbackRegion) override;
	
	void updateAddressLabel(juce::StringRef newAddress);

private:
    juce::ARAPlaybackRegion& playbackRegion;
	WaveformCache& waveformCache;

	std::unique_ptr<ActiveRegionView> activeRegionView;
	std::unique_ptr<AudioModView> audioModView;
	std::unique_ptr<AudioSourceView> audioSourceView;
	
	std::unique_ptr<juce::Label> memoryAddressLabel;
	std::unique_ptr<juce::Label> notificationLabel;

	int numNotifications = 0;
	
	void _drawAudioSource(juce::Graphics& g);
	void _drawPlaybackRegion(juce::Graphics& g);
	void _updateRegionBounds();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackRegionView);
};
