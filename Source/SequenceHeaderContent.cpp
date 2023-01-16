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
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SequenceHeaderContent::~SequenceHeaderContent()
{
    headers.clear();
}

void SequenceHeaderContent::paint (juce::Graphics& g)
{

}

void SequenceHeaderContent::resized()
{
    for(size_t orderIndex = 0; orderIndex < headers.size(); orderIndex++)
    {
        auto yPos = orderIndex * araSection.getZoomState().getTrackHeight();
        headers[orderIndex]->setTopLeftPosition(0, yPos);
    }
}


void SequenceHeaderContent::addRegionSequence(juce::ARARegionSequence *sequence)
{
    int orderIndex = sequence->getOrderIndex();
    auto newHeader = new SequenceHeader(araSection, *sequence);
    headers.insert(orderIndex, newHeader);
    newHeader = nullptr;
}

void SequenceHeaderContent::updateZoomState()
{
    for(auto header : headers)
        header->updateZoomState();
    
    auto width = araSection.getZoomState().getHeaderWidth();
    auto numHeaders = headers.size();
    auto height = araSection.getZoomState().getTrackHeight() * numHeaders;
    
    this->setSize(width, height);
}
