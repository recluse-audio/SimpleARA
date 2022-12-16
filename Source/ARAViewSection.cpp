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
//==============================================================================
ARAViewSection::ARAViewSection(SimpleARAEditor& editor) : mEditor(editor)
{
    waveCache = std::make_unique<WaveformCache>();
    
    auto document = mEditor.getARADocument();
    
    if(document != nullptr)
        _initializeViews(document);

    
}

ARAViewSection::~ARAViewSection()
{
}

void ARAViewSection::_initializeViews(juce::ARADocument* document)
{
    auto docSpecialisation = mEditor.getARADocumentSpecialisation();

    documentView = std::make_unique<DocumentView> (mEditor, *document, mEditor.getPlayHeadState(), *waveCache.get() );
    addChildComponent(documentView.get());
    
    /** TO DO : make regionZero into the last selected region */
    auto regionZero = static_cast<ARA_PlaybackRegion*>(docSpecialisation->getRegionAtIndex(0));
    playbackRegionView = std::make_unique<PlaybackRegionView>(mEditor, *regionZero, *waveCache.get() );
    addChildComponent(playbackRegionView.get());
}

void ARAViewSection::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey.withAlpha(0.7f));
}

void ARAViewSection::resized()
{
    if(documentView != nullptr)
        documentView->setBoundsRelative(0.f, 0.f, 1.f, 1.f);
    
    if(playbackRegionView != nullptr)
        playbackRegionView->setBoundsRelative(0.f, 0.f, 1.f, 1.f);

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
    documentView->setVisible(true);
    playbackRegionView->setVisible(false);
}

//=======================
void ARAViewSection::setSequenceFocus()
{
    
}

//=======================
void ARAViewSection::setRegionFocus()
{
    documentView->setVisible(false);
    playbackRegionView->setVisible(true);
}
