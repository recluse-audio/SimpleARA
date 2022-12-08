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
    auto docSpecialisation = mEditor.getARADocumentSpecialisation();
    
    if(document != nullptr)
    {
        documentView = std::make_unique<DocumentView> (mEditor, *document, mEditor.getPlayHeadState(), *waveCache.get() );
        addAndMakeVisible (documentView.get());
        //addChildComponent(documentView.get());
        
        auto regionZero = static_cast<ARA_PlaybackRegion*>(docSpecialisation->getRegionAtIndex(0));
        playbackRegionView = std::make_unique<PlaybackRegionView>(mEditor, *regionZero, *waveCache.get() );
        //addAndMakeVisible(playbackRegionView.get());
        addChildComponent(playbackRegionView.get());
    }
    
    
//    if (auto* editorView = mEditor.getARAEditorView())
//    {
//        auto* document = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentSpecialisation>(editorView->getDocumentController())->getDocument();
//        documentView = std::make_unique<DocumentView> (mEditor, *document, mEditor.getPlayHeadState() );
////        addAndMakeVisible (documentView.get());
//        addChildComponent(documentView.get());
//
//
//
//    }


}

ARAViewSection::~ARAViewSection()
{
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

