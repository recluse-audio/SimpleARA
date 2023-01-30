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
#include "ARA_RegionSequence.h"
#include "WaveformCache.h"
#include "PlayheadMarker.h"
#include "ARAViewSection.h"
#include "RegionSequenceView.h"
#include "TimeGrid.h"
#include "PlayHeadOverlay.h"
#include "ZoomState.h"
//==============================================================================
DocumentView::DocumentView(ARAViewSection& section, juce::ARADocument& document)
: araSection(section)
, araDocument (document)
, zoomState(section.getZoomState())
{
    playheadMarker = std::make_unique<PlayheadMarker>();
    playheadMarker->setAlwaysOnTop(true);
    addAndMakeVisible(playheadMarker.get());

    zoomState.addChangeListener(this);
}

DocumentView::~DocumentView()
{
	sequenceViews.clear();
    timeGrid.release();
    playheadMarker.release();
	zoomState.removeChangeListener(this);
}


//=================
void DocumentView::paint (juce::Graphics& g)
{
	//g.fillAll(juce::Colours::grey);
	
	auto outline = this->getBounds();
	g.setColour(juce::Colours::darkgrey.darker());
	g.fillRect(outline);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Doc Controller View",
					  getLocalBounds(),
					  Justification::centred,
					  1);
}


//=================
void DocumentView::resized()
{
	
	for(auto sequenceView : sequenceViews)
	{
		int index = sequenceView->getOrderIndex();
		auto yPos = index * zoomState.getTrackHeight();
		sequenceView->setTopLeftPosition(0, yPos);
	}

}


//===============
void DocumentView::updateZoomState()
{
	auto regionSequences = araDocument.getRegionSequences();
	
	auto width = this->_getMaxDuration() * zoomState.getPixelsPerSecond();
	
	int sequenceCount = sequenceViews.size();
	int minimum = 12; // even with 0 sequences we will still want the doc view to be a certain height
	int numSequences = ( sequenceCount > minimum) ? sequenceCount : minimum;
			
	auto height = numSequences * zoomState.getTrackHeight();
	
	this->setSize(width, height);
	
	
}

//================
void DocumentView::updatePlayheadPosition(double positionInSeconds)
{
    auto proportionOfDuration = positionInSeconds / _getMaxDuration();
    auto playheadPositionInPixels = this->getWidth() * proportionOfDuration;
    playheadMarker->setBounds((int)playheadPositionInPixels, 0, 3, this->getHeight());
}







//===============
void DocumentView::clear()
{

}

//================
void DocumentView::addRegionSequence(juce::ARARegionSequence *newSequence)
{
	auto sequenceView = new RegionSequenceView(araSection, *newSequence);
	
	addAndMakeVisible(sequenceView);
	sequenceViews.add(sequenceView);
	
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
	
	auto regionSequences = araDocument.getRegionSequences<ARA_RegionSequence>();
	
	/** Region sequences don't return end positions, probably should subclass that, for now ask the component view of it*/
	for(auto sequence : regionSequences)
	{
		if(sequence->getEndOfLastRegion() > maxDuration)
			maxDuration = sequence->getEndOfLastRegion();
	}
	return maxDuration;
}


void DocumentView::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if(source == &zoomState)
		updateZoomState();
}
