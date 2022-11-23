/*
  ==============================================================================

    WaveformCache.cpp
    Created: 2 Nov 2022 12:21:53pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "WaveformCache.h"

WaveformCache::WaveformCache() : thumbnailCache (20)
{
}

WaveformCache::~WaveformCache()
{
	for (const auto& entry : thumbnails)
	{
		entry.first->removeListener (this);
	}
}

//==============================================================================
void WaveformCache::willDestroyAudioSource (ARAAudioSource* audioSource)
{
	removeAudioSource (audioSource);
}

AudioThumbnail& WaveformCache::getOrCreateThumbnail (ARAAudioSource* audioSource)
{
	const auto iter = thumbnails.find (audioSource);

	if (iter != std::end (thumbnails))
		return *iter->second;

	auto thumb = std::make_unique<AudioThumbnail> (128, dummyManager, thumbnailCache);
	auto& result = *thumb;

	++hash;
	thumb->setReader (new ARAAudioSourceReader (audioSource), hash);

	audioSource->addListener (this);
	thumbnails.emplace (audioSource, std::move (thumb));
	return result;
}


//======================
// PRIVATE FUNCTIONS

void WaveformCache::removeAudioSource (ARAAudioSource* audioSource)
{
	audioSource->removeListener (this);
	thumbnails.erase (audioSource);
}
