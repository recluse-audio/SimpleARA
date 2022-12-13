/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for an ARA playback renderer implementation.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <JuceHeader.h>
#include "UtilObjects.h"
#include "PossiblyBufferedReader.h"

//==============================================================================
/**
*/
//==============================================================================
class ARA_PlaybackRenderer  : public ARAPlaybackRenderer
{
public:
	using ARAPlaybackRenderer::ARAPlaybackRenderer;

	void prepareToPlay (double sampleRateIn,
						int maximumSamplesPerBlockIn,
						int numChannelsIn,
						AudioProcessor::ProcessingPrecision,
						AlwaysNonRealtime alwaysNonRealtime) override;

	void releaseResources() override;

	bool processBlock (AudioBuffer<float>& buffer,
					   AudioProcessor::Realtime realtime,
					   const AudioPlayHead::PositionInfo& positionInfo) noexcept override;

	using ARAPlaybackRenderer::processBlock;

private:
	//==============================================================================
	// We're subclassing here only to provide a proper default c'tor for our shared resource

	bool useBufferedAudioSourceReader = true;
	int numChannels = 2;
	double sampleRate = 48000.0;
	int maximumSamplesPerBlock = 128;
	
	SharedResourcePointer<SharedTimeSliceThread> sharedTimesliceThread;
	
	std::map<ARA::PlugIn::AudioSource*, PossiblyBufferedReader> audioSourceReaders;
	
	std::unique_ptr<AudioBuffer<float>> tempBuffer;
    
    /** Checks if an audio source matches the host in channel layout and sample rate etc.*/
    bool _sourceMatchesHost(juce::ARAAudioSource* source);
};
