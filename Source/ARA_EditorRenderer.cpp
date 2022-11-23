/*
  ==============================================================================

    PluginARAEditorRenderer.cpp
    Created: 1 Nov 2022 12:46:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_EditorRenderer.h"

ARA_EditorRenderer::ARA_EditorRenderer (ARA::PlugIn::DocumentController* documentController)
	: juce::ARAEditorRenderer (documentController)
{
}

ARA_EditorRenderer::~ARA_EditorRenderer()
{
	for (const auto& rs : regionSequences)
		rs->removeListener (this);
}

void ARA_EditorRenderer::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence*, juce::ARAPlaybackRegion*)
{
}

void ARA_EditorRenderer::didAddRegionSequence (ARA::PlugIn::RegionSequence* rs) noexcept
{
	auto* sequence = dynamic_cast<ARARegionSequence*> (rs);
	sequence->addListener (this);
	regionSequences.insert (sequence);
}

void ARA_EditorRenderer::didAddPlaybackRegion (ARA::PlugIn::PlaybackRegion*) noexcept
{
}

void ARA_EditorRenderer::prepareToPlay (double sampleRateIn,
					int maximumExpectedSamplesPerBlock,
					int numChannels,
					AudioProcessor::ProcessingPrecision,
					AlwaysNonRealtime alwaysNonRealtime)
{
	sampleRate = sampleRateIn;
	ignoreUnused (maximumExpectedSamplesPerBlock, alwaysNonRealtime);
}


void ARA_EditorRenderer::releaseResources()
{
	audioSourceReaders.clear();
}

void ARA_EditorRenderer::reset()
{
}

bool ARA_EditorRenderer::processBlock (AudioBuffer<float>& buffer,
				   AudioProcessor::Realtime realtime,
				   const AudioPlayHead::PositionInfo& positionInfo) noexcept
{
	return true;
}




//=========================
// PRIVATE FUNCTIONS



