/*
  ==============================================================================

    SequenceHeaderContent.cpp
    Created: 2 Jan 2023 12:18:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SequenceHeaderContent.h"
#include "SequenceHeader.h"
#include "ZoomState.h"
//==============================================================================
SequenceHeaderContent::SequenceHeaderContent(ARAViewSection& section, juce::ARADocument& document)
: araSection(section)
, araDocument(document)
, ZoomStateListener(section.getZoomState())
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

//======================
SequenceHeaderContent::~SequenceHeaderContent()
{
    headers.clear();
}


//======================
void SequenceHeaderContent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::green);
}


//======================
void SequenceHeaderContent::resized()
{
	for(auto header : headers)
	{
		int index = header->getOrderIndex() - 1;
		auto yPos = index * getZoomState().getTrackHeight();
		header->setTopLeftPosition(0, yPos);
	}

}

//======================
void SequenceHeaderContent::addRegionSequence(juce::ARARegionSequence *sequence)
{
    auto newHeader = new SequenceHeader(araSection, *sequence);
	addAndMakeVisible(newHeader);
	headers.add(newHeader);
}


//======================
void SequenceHeaderContent::updateZoomState()
{
    for(auto header : headers)
        header->updateZoomState();
    
    auto width = getZoomState().getHeaderWidth();
    auto numHeaders = headers.size();
	if(numHeaders < 12)
		numHeaders = 12;
	
    auto height = getZoomState().getTrackHeight() * numHeaders;
	
    this->setSize(width, height);
}
