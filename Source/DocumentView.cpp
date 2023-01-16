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
#include "TimeGrid.h"
#include "PlayHeadOverlay.h"
#include "ZoomState.h"
//==============================================================================
DocumentView::DocumentView(ARAViewSection& section, juce::ARADocument& document)
: araSection(section),
araDocument (document),
zoomState(section.getZoomState())
{
    playheadMarker = std::make_unique<PlayheadMarker>();
    playheadMarker->setAlwaysOnTop(true);
    addAndMakeVisible(playheadMarker.get());

	updateZoomState();
    //araDocument.addListener(this);
}

DocumentView::~DocumentView()
{
    timeGrid.release();
    playheadMarker.release();
}


void DocumentView::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::grey);
	
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
	repaint();
}


void DocumentView::updatePlayheadPosition(double positionInSeconds)
{
    auto proportionOfDuration = positionInSeconds / _getMaxDuration();
    auto playheadPositionInPixels = this->getWidth() * proportionOfDuration;
    playheadMarker->setBounds((int)playheadPositionInPixels, 0, 3, this->getHeight());
}





//===============
void DocumentView::updateZoomState()
{
    for(auto sequence : regionSequences)
    {
        sequence->updateZoomState();
    }
    
    auto width = this->_getMaxDuration() * zoomState.getPixelsPerSecond();
	
	int sequenceCount = regionSequences.size();
	int minimum = 12; // even with 0 sequences we will still want the doc view to be a certain height
	int numSequences = ( sequenceCount > minimum) ? sequenceCount : minimum;
			
    auto height = numSequences * zoomState.getTrackHeight();
    
    this->setSize(width, height);
    
    
}

//===============
void DocumentView::clear()
{
    regionSequences.clear();
}

//================
void DocumentView::addRegionSequence(juce::ARARegionSequence *newSequence)
{
	auto sequenceView = new RegionSequenceView(araSection, *newSequence);
	
	// don't re-add an existing view.  Happens due to weird timing of calls to ara listeners in different hosts
	if(regionSequences.contains(sequenceView))
		return;
	
	addAndMakeVisible(sequenceView);
	regionSequences.add(sequenceView);
	
	updateZoomState();
}

//================
double DocumentView::getDuration() const
{
	return _getMaxDuration();
}


//================
double DocumentView::_getMaxDuration() const
{
	double maxDuration = 120.0;  //
	
	/** Region sequences don't return end positions, probably should subclass that, for now ask the component view of it*/
	for(auto sequence : regionSequences)
	{
		if(sequence->getEndOfLastRegion() > maxDuration)
			maxDuration = sequence->getEndOfLastRegion();
	}
	return maxDuration;
}
