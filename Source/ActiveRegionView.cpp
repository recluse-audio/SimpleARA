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
#include "PluginEditor.h"
#include "HelperDisplay.h"
#include "ARA_PlaybackRegion.h"
#include "ARAViewSection.h"


//==============================================================================
ActiveRegionView::ActiveRegionView(ARAViewSection& section, ARA_PlaybackRegion& region)
: araSection(section)
, playbackRegion(region)
, waveCache(section.getWaveCache())
{

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ActiveRegionView::~ActiveRegionView()
{
}

void ActiveRegionView::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);

    if(playbackRegion.isCurrentlyInView())
        g.setColour(juce::Colours::yellow);
    else
        g.setColour(juce::Colours::red);
    
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
	
	thumbnail.drawChannels (g, bounds, regionStartInMod, regionEndInMod, 1.0f);
}

void ActiveRegionView::mouseEnter(const juce::MouseEvent& e)
{
	auto helperDisplay = araSection.getEditor().getHelperDisplay();
	helperDisplay->displayPlaybackRegion(playbackRegion);
}

void ActiveRegionView::mouseExit(const juce::MouseEvent& e)
{
	auto helperDisplay = araSection.getEditor().getHelperDisplay();
	helperDisplay->clearDisplay();
    
}
