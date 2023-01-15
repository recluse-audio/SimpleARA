/*
  ==============================================================================

    ARAViewSection.cpp
    Created: 2 Dec 2022 6:42:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARAViewSection.h"
#include "DocumentView.h"
#include "PlaybackRegionView.h"
#include "WaveformCache.h"
#include "ARA_DocumentSpecialisation.h"
#include "PluginEditor.h"
#include "ARA_PlaybackRegion.h"
#include "MultiTrackTimeline.h"
#include "TrackLane.h"
#include "TimeRuler.h"
#include "SequenceHeaderContent.h"
//==============================================================================
ARAViewSection::ARAViewSection(SimpleARAEditor& editor) : mEditor(editor)
, playheadState(editor.getPlayHeadState())
{
    waveCache = std::make_unique<WaveformCache>();
    
    timeRulerContent = std::make_unique<TimeRuler>();
    timeRulerViewport = std::make_unique<juce::Viewport>();
    timeRulerViewport->setViewedComponent(timeRulerContent.get());
    addAndMakeVisible(timeRulerViewport.get());
    
    
    headerContent = std::make_unique<SequenceHeaderContent>();
    headerViewport = std::make_unique<juce::Viewport>();
    headerViewport->setViewedComponent(headerContent.get());
    addAndMakeVisible(headerViewport.get());
    
    
    auto document = mEditor.getARADocument();
    
    if(document != nullptr)
        _initializeViews(document);

    zoomState = std::make_unique<ZoomState>();
    
    rebuildFromDocument();
    
    this->startTimerHz(60);
    
}

ARAViewSection::~ARAViewSection()
{
}

void ARAViewSection::_initializeViews(juce::ARADocument* document)
{
    auto docSpecialisation = mEditor.getARADocumentSpecialisation();

    documentContent = std::make_unique<DocumentView> (mEditor, *document, *waveCache.get() );
    documentViewport = std::make_unique<juce::Viewport>();
    documentViewport->setViewedComponent(documentContent.get());
    addAndMakeVisible(documentViewport.get());
    
//
//    /** TO DO : make regionZero into the last selected region */
//    auto regionZero = static_cast<ARA_PlaybackRegion*>(docSpecialisation->getRegionAtIndex(0));
//    playbackRegionView = std::make_unique<PlaybackRegionView>(mEditor, *regionZero, *waveCache.get() );
//    addChildComponent(playbackRegionView.get());
}

void ARAViewSection::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::pink.withAlpha(0.7f));
}

void ARAViewSection::resized()
{
    auto bounds = this->getLocalBounds();
    auto localWidth = bounds.getWidth();
    auto localHeight = bounds.getHeight();;
    auto headerWidth = zoomState->getHeaderWidth();
    auto trackHeight = zoomState->getTrackHeight();
    auto timeRulerHeight = zoomState->getTimeRulerHeight();
    auto widthMinusHeader = localWidth - headerWidth;
    auto heightMinusRuler = localHeight - timeRulerHeight;
    
    headerViewport->setBounds   (0, timeRulerHeight, headerWidth, heightMinusRuler);
    timeRulerViewport->setBounds(headerWidth, 0, widthMinusHeader, timeRulerHeight);
    documentViewport->setBounds(headerWidth, timeRulerHeight, widthMinusHeader, heightMinusRuler);

}

//========================
//void ARAViewSection::setFocus(SimpleARAEditor::FocusView focus)
//{
////    switch(focus)
////    {
////        case 0:
////            documentView->setVisible(true);
////            playbackRegionView->setVisible(false);
////        case 1:
////            documentView->setVisible(false);
////            playbackRegionView->setVisible(true);
////    }
//}

//=======================
void ARAViewSection::setDocumentFocus()
{
    //documentView->setVisible(true);
    //playbackRegionView->setVisible(false);
}

//=======================
void ARAViewSection::setSequenceFocus()
{
    
}

//=======================
void ARAViewSection::setRegionFocus()
{
    //documentView->setVisible(false);
    //playbackRegionView->setVisible(true);
}


//=======================
void ARAViewSection::_updateZoomState()
{
    timeRulerContent->updateZoomState();
    headerContent->updateZoomState();
    documentContent->updateZoomState();


}

//======================
void ARAViewSection::timerCallback()
{
    documentContent->updatePlayheadPosition(playheadState.timeInSeconds);
}


//======================
juce::ARADocument& ARAViewSection::getARADocument()
{
    return *mEditor.getARADocument();
}

//======================
ZoomState& ARAViewSection::getZoomState()
{
    return *zoomState.get();
}

//=====================
SimpleARAEditor& ARAViewSection::getEditor()
{
    return mEditor;
}

//=====================
WaveformCache& ARAViewSection::getWaveCache()
{
    return *waveCache.get();
}

//======================
void ARAViewSection::didAddRegionSequenceToDocument (juce::ARADocument* doc, juce::ARARegionSequence* sequence)
{
    _addRegionSequence(sequence);
}



// clears current
void ARAViewSection::rebuildFromDocument()
{
    headerContent.reset();
    documentContent.reset();
    
    headerContent = std::make_unique<SequenceHeaderContent>(this, *mEditor.getARADocument());
    documentContent = std::make_unique<DocumentView>(this, *mEditor.getARADocument());
    
    headerViewport->setViewedComponent(headerContent.get());
    documentViewport->setViewedComponent(documentContent.get());
    
    auto regionSequences = mEditor.getARADocument()->getRegionSequences();
    for(auto sequence : regionSequences)
    {
        _addRegionSequence(sequence);
    }
    
}

//======================
void ARAViewSection::_addRegionSequence(juce::ARARegionSequence* sequence)
{
    headerContent->addRegionSequence(sequence);
    documentContent->addRegionSequence(sequence);
}
