/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for an ARA playback renderer implementation.

  ==============================================================================
*/

#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioMod.h"
#include "ARA_PlaybackRegion.h"

//==============================================================================
void ARA_PlaybackRenderer::prepareToPlay (double sampleRateIn, int maximumSamplesPerBlockIn, int numChannelsIn, juce::AudioProcessor::ProcessingPrecision, AlwaysNonRealtime alwaysNonRealtime)
{
	numChannels = numChannelsIn;
	sampleRate = sampleRateIn;
	maximumSamplesPerBlock = maximumSamplesPerBlockIn;
	
	tempBuffer.reset (new juce::AudioBuffer<float> (numChannels, maximumSamplesPerBlock));

	useBufferedAudioSourceReader = alwaysNonRealtime == AlwaysNonRealtime::no;

	for (const auto playbackRegion : getPlaybackRegions<ARA_PlaybackRegion>())
	{
        playbackRegion->setSampleRate(sampleRateIn);

		auto audioSource = playbackRegion->getAudioModification()->getAudioSource();
        
		if (audioSourceReaders.find (audioSource) == audioSourceReaders.end())
		{
			auto reader = std::make_unique<juce::ARAAudioSourceReader> (audioSource);

			if (! useBufferedAudioSourceReader)
			{
				audioSourceReaders.emplace (audioSource, PossiblyBufferedReader { std::move (reader) });
			}
			else
			{
				double fourBlocks = 4.0 * maximumSamplesPerBlock;
				double twoSeconds = 2.0 * sampleRate;
				const auto readAheadSize = juce::jmax (fourBlocks, twoSeconds);
				
				
				audioSourceReaders.emplace (audioSource, PossiblyBufferedReader { std::make_unique<juce::BufferingAudioReader> (reader.release(), *sharedTimesliceThread, readAheadSize) });
			}
		}
	}
}

void ARA_PlaybackRenderer::releaseResources()
{
	audioSourceReaders.clear();
	tempBuffer.reset();
}

//==============================================================================
bool ARA_PlaybackRenderer::processBlock (juce::AudioBuffer<float>& buffer,
                                                       juce::AudioProcessor::Realtime realtime,
                                                       const juce::AudioPlayHead::PositionInfo& positionInfo) noexcept
{
	const auto numSamples = buffer.getNumSamples();
	jassert (numSamples <= maximumSamplesPerBlock);
	jassert (numChannels == buffer.getNumChannels());
	jassert (realtime == AudioProcessor::Realtime::no || useBufferedAudioSourceReader);
	const auto blockTimePosInSamples = positionInfo.getTimeInSamples().orFallback (0);
	const auto isPlaying = positionInfo.getIsPlaying();

	bool success = true;
	bool didRenderAnyRegion = false;

    
	if (isPlaying)
	{
		const auto blockRange = Range<int64>::withStartAndLength (blockTimePosInSamples, numSamples);

		for (const auto& playbackRegion : getPlaybackRegions<ARA_PlaybackRegion>())
		{
	

            auto readRange = playbackRegion->getRangeToReadInAudioSource(blockRange);
            if(readRange.isEmpty())
                continue;
            


			// Get the audio source for the region and find the reader for that source.
			const auto audioSource = playbackRegion->getAudioModification()->getAudioSource();
			const auto readerIt = audioSourceReaders.find (audioSource);

            bool sourceAndHostMatch = this->_sourceMatchesHost(audioSource);
            
			if ( !sourceAndHostMatch || (readerIt == audioSourceReaders.end()))
			{
				success = false;
				continue;
			}

			auto& reader = readerIt->second;
			reader.setReadTimeout (realtime == AudioProcessor::Realtime::no ? 100 : 0);

            
			// Calculate buffer offsets.
			const int numSamplesToRead = (int) readRange.getLength();
			const int startInBuffer = (int) (readRange.getStart() - blockRange.getStart());
			auto startInSource = readRange.getStart() + playbackRegion->getModOffset();

            
			// Read samples:
			// first region can write directly into output, later regions need to use local buffer.
			auto& readBuffer = (didRenderAnyRegion) ? *tempBuffer : buffer;

			if (! reader.get()->read (&readBuffer, startInBuffer, numSamplesToRead, startInSource, true, true))
			{
				success = false;
				continue;
			}

            auto gain = playbackRegion->getAudioModification<ARA_AudioMod>()->getParameterValue("GAIN");
            readBuffer.applyGain(gain);
            
			if (didRenderAnyRegion)
			{
				// Mix local buffer into the output buffer.
				for (int c = 0; c < numChannels; ++c)
					buffer.addFrom (c, startInBuffer, *tempBuffer, c, startInBuffer, numSamplesToRead);
			}
			else
			{
				// Clear any excess at start or end of the region.
				if (startInBuffer != 0)
					buffer.clear (0, startInBuffer);

				const int endInBuffer = startInBuffer + numSamplesToRead;
				const int remainingSamples = numSamples - endInBuffer;

				if (remainingSamples != 0)
					buffer.clear (endInBuffer, remainingSamples);

				didRenderAnyRegion = true;
			}
		}
	}

	// If no playback or no region did intersect, clear buffer now.
	if (! didRenderAnyRegion)
		buffer.clear();

	return success;
}


//============================
bool ARA_PlaybackRenderer::_sourceMatchesHost(juce::ARAAudioSource* audioSource)
{
    auto audioSourceTuple = std::make_tuple (audioSource->getChannelCount(), audioSource->getSampleRate());
    auto hostTuple = std::make_tuple (numChannels, sampleRate);
    bool sourceAndHostMatch = (audioSourceTuple == hostTuple);
    return sourceAndHostMatch;
}
