/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for an ARA playback renderer implementation.

  ==============================================================================
*/

#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioMod.h"

//==============================================================================
void ARA_PlaybackRenderer::prepareToPlay (double sampleRateIn, int maximumSamplesPerBlockIn, int numChannelsIn, juce::AudioProcessor::ProcessingPrecision, AlwaysNonRealtime alwaysNonRealtime)
{
	numChannels = numChannelsIn;
	sampleRate = sampleRateIn;
	maximumSamplesPerBlock = maximumSamplesPerBlockIn;
	
	tempBuffer.reset (new juce::AudioBuffer<float> (numChannels, maximumSamplesPerBlock));

	useBufferedAudioSourceReader = alwaysNonRealtime == AlwaysNonRealtime::no;

	for (const auto playbackRegion : getPlaybackRegions())
	{
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

		for (const auto& playbackRegion : getPlaybackRegions())
		{
			// Evaluate region borders in song time, calculate sample range to render in song time.
			// Note that this example does not use head- or tailtime, so the includeHeadAndTail
			// parameter is set to false here - this might need to be adjusted in actual plug-ins.
			juce::Range<int64> playbackRegionSampleRange { playbackRegion->getStartInPlaybackSamples(sampleRate),
												   playbackRegion->getEndInPlaybackSamples(sampleRate) };
			
 			auto renderRange = blockRange.getIntersectionWith (playbackRegionSampleRange);

			if (renderRange.isEmpty())
				continue;

			// Evaluate region borders in modification/source time and calculate offset between
			// song and source samples, then clip song samples accordingly
			// (if an actual plug-in supports time stretching, this must be taken into account here).
			juce::Range<int64> modificationSampleRange { playbackRegion->getStartInAudioModificationSamples(),
												   playbackRegion->getEndInAudioModificationSamples() };
			
			const auto modificationSampleOffset = modificationSampleRange.getStart() - playbackRegionSampleRange.getStart();

			renderRange = renderRange.getIntersectionWith (modificationSampleRange.movedToStartAt (playbackRegionSampleRange.getStart()));

			if (renderRange.isEmpty())
				continue;

			// Get the audio source for the region and find the reader for that source.
			// This simplified example code only produces audio if sample rate and channel count match -
			// a robust plug-in would need to do conversion, see ARA SDK documentation.
			const auto audioSource = playbackRegion->getAudioModification()->getAudioSource();
			const auto readerIt = audioSourceReaders.find (audioSource);

			auto audioSourceTuple = std::make_tuple (audioSource->getChannelCount(), audioSource->getSampleRate());
			auto hostTuple = std::make_tuple (numChannels, sampleRate);
			bool sourceAndHostMatch = (audioSourceTuple == hostTuple);
			if ( !sourceAndHostMatch || (readerIt == audioSourceReaders.end()))
			{
				success = false;
				continue;
			}

			auto& reader = readerIt->second;
			reader.setReadTimeout (realtime == AudioProcessor::Realtime::no ? 100 : 0);

			// Calculate buffer offsets.
			const int numSamplesToRead = (int) renderRange.getLength();
			const int startInBuffer = (int) (renderRange.getStart() - blockRange.getStart());
			auto startInSource = renderRange.getStart() + modificationSampleOffset;

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
