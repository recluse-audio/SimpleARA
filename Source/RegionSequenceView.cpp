/*
  ==============================================================================

    RegionSequenceView.cpp
    Created: 1 Nov 2022 12:48:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RegionSequenceView.h"
#include "GlobalDefines.h"

//==============================================================================
RegionSequenceView::RegionSequenceView(ARARegionSequence& rs, WaveformCache& wave, double pixelPerSec)
: regionSequence (rs), waveformCache(wave), zoomLevelPixelPerSecond (pixelPerSec)
{
	regionSequence.addListener (this);

	for (auto* playbackRegion : regionSequence.getPlaybackRegions())
		createAndAddPlaybackRegionView (playbackRegion);

	updatePlaybackDuration();
}

RegionSequenceView::~RegionSequenceView()
{
	regionSequence.removeListener (this);

	for (const auto& it : playbackRegionViewsMap)
		it.first->removeListener (this);
}

void RegionSequenceView::paint(juce::Graphics &g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::yellow.withAlpha(0.1f));
	g.fillRect(outline);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Region Sequence View", getLocalBounds(), Justification::centred, 1);
}

//==============================================================================
// ARA Document change callback overrides
void RegionSequenceView::willRemovePlaybackRegionFromRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	removeChildComponent (playbackRegionViewsMap[playbackRegion].get());
	playbackRegionViewsMap.erase (playbackRegion);
	updatePlaybackDuration();
}

void RegionSequenceView::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	createAndAddPlaybackRegionView (playbackRegion);
	updatePlaybackDuration();
}

void RegionSequenceView::willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	removeChildComponent (playbackRegionViewsMap[playbackRegion].get());
	playbackRegionViewsMap.erase (playbackRegion);
	updatePlaybackDuration();
}

void RegionSequenceView::willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* playbackRegion, juce::ARAPlaybackRegion::PropertiesPtr regionProperties)
{
}

void RegionSequenceView::didUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion*)
{
	updatePlaybackDuration();
}

void RegionSequenceView::resized()
{
	for (auto& pbr : playbackRegionViewsMap)
	{
		const auto playbackRegion = pbr.first;
		auto regionView = pbr.second.get();
		
		auto sourceStartInTimeline = getAudioSourceStartInTimeLine(playbackRegion);
		
		auto sourceDuration = playbackRegion->getAudioModification()->getAudioSource()->getDuration();
		
		const auto xPos = roundToInt(sourceStartInTimeline * zoomLevelPixelPerSecond);
		const auto width = roundToInt (sourceDuration * zoomLevelPixelPerSecond);
		
		auto regionViewBounds = juce::Rectangle<int>(xPos, 5, width, this->getHeight() - 10);
		regionView->setBounds(regionViewBounds);
	}
}

double RegionSequenceView::getPlaybackDuration() const noexcept
{
	return playbackDuration;
}

void RegionSequenceView::setZoomLevel (double pixelPerSecond)
{
	zoomLevelPixelPerSecond = pixelPerSecond;
	resized();
}




//========================
// PRIVATE FUNCTIONS

void RegionSequenceView::createAndAddPlaybackRegionView (ARAPlaybackRegion* playbackRegion)
{
	playbackRegionViewsMap[playbackRegion] = std::make_unique<PlaybackRegionView> (*playbackRegion, waveformCache);
	playbackRegion->addListener (this);
	addAndMakeVisible (*playbackRegionViewsMap[playbackRegion]);
}


void RegionSequenceView::updatePlaybackDuration()
{
	const auto iter = std::max_element (
		playbackRegionViewsMap.begin(),
		playbackRegionViewsMap.end(),
		[] (const auto& a, const auto& b) { return a.first->getEndInPlaybackTime() < b.first->getEndInPlaybackTime(); });

	playbackDuration = iter != playbackRegionViewsMap.end() ? iter->first->getEndInPlaybackTime() : 0.0;

	sendChangeMessage();
}



