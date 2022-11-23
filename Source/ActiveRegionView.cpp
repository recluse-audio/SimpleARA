/*
  ==============================================================================

    ActiveRegionView.cpp
    Created: 20 Nov 2022 5:21:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ActiveRegionView.h"
#include "WaveformCache.h"
//==============================================================================
ActiveRegionView::ActiveRegionView(juce::ARAPlaybackRegion& region, WaveformCache& cache)
: playbackRegion(region), waveCache(cache)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ActiveRegionView::~ActiveRegionView()
{
}

void ActiveRegionView::paint (juce::Graphics& g)
{
	g.setColour(juce::Colours::aquamarine);
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 1.f, 1.f);
	
	_drawPlaybackRegion(g);
}

void ActiveRegionView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ActiveRegionView::_drawPlaybackRegion(juce::Graphics& g)
{
	auto bounds = this->getLocalBounds();
	
	auto audioSource = playbackRegion.getAudioModification()->getAudioSource();
	auto& thumbnail = waveCache.getOrCreateThumbnail(audioSource);
	
	// Draw just the region
	auto regionStartInMod = playbackRegion.getStartInAudioModificationTime();
	auto regionEndInMod = playbackRegion.getEndInAudioModificationTime();
	
	g.setColour (Colours::mediumaquamarine);
	thumbnail.drawChannels (g, bounds, regionStartInMod, regionEndInMod, 1.0f);
}
