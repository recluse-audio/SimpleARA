/*
  ==============================================================================

    DocumentView.cpp
    Created: 1 Nov 2022 12:50:54pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DocumentView.h"
#include "PluginEditor.h"
#include "ARA_PlaybackRegion.h"
#include "WaveformCache.h"
#include "PlayheadMarker.h"
#include "ARAViewSection.h"
#include "RegionSequenceView.h"
//==============================================================================
DocumentView::DocumentView(ARAViewSection& section, juce::ARADocument& document)
: araSection(section),
araDocument (document),
zoomState(section.getZoomState())
{
    playheadMarker = std::make_unique<PlayheadMarker>();
    playheadMarker->setAlwaysOnTop(true);
    addAndMakeVisible(playheadMarker.get());

    //araDocument.addListener(this);
}

DocumentView::~DocumentView()
{
    timeGrid.release();
    playheadMarker.release();
}


void DocumentView::paint (juce::Graphics& g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::red);
	g.drawRect(outline, 2.f);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Doc Controller View",
					  getLocalBounds(),
					  Justification::centred,
					  1);
}

void DocumentView::resized()
{
    for(size_t i = 0; i < regionSequences.size(); i++)
    {
        auto yPos = i * zoomState.getTrackHeight();
        regionSequences[i]->setTopLeftPosition(0, yPos);
    }
}


void DocumentView::updatePlayheadPosition(double positionInSeconds)
{
    auto proportionOfDuration = positionInSeconds / _getMaxDuration();
    auto playheadPositionInPixels = this->getWidth() * proportionOfDuration;
    playheadMarker->setBounds((int)playheadPositionInPixels, 0, 3, this->getHeight());
}

//================
double DocumentView::_getMaxDuration() const
{
    /** TO DO:  Actual code here, not just a fixed number */
    return 120.0;
}



//===============
void DocumentView::updateZoomState()
{
    for(auto sequence : regionSequences)
    {
        sequence->updateZoomState();
    }
    
    auto width = this->_getMaxDuration() * zoomState.getPixelsPerSecond();
    auto height = regionSequences.size() * zoomState.getTrackHeight();
    
    this->setSize(width, height);
    
    
}
