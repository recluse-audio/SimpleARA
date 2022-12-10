/*
  ==============================================================================

	ARA_DocumentController.cpp
    Created: 2 Nov 2022 10:55:15am
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_DocumentSpecialisation.h"
#include "ARA_EditorRenderer.h"
#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioMod.h"
#include "ARA_PlaybackRegion.h"
#include "CallbackTracker.h"

ARA_DocumentSpecialisation::ARA_DocumentSpecialisation(const ARA::PlugIn::PlugInEntry* entry, const ARA::ARADocumentControllerHostInstance* instance)
: juce::ARADocumentControllerSpecialisation(entry, instance)
{
	
}

juce::ARAPlaybackRenderer* ARA_DocumentSpecialisation::doCreatePlaybackRenderer() noexcept
{
	return new ARA_PlaybackRenderer (getDocumentController());
}

juce::ARAEditorRenderer* ARA_DocumentSpecialisation::doCreateEditorRenderer() noexcept
{
	return new ARA_EditorRenderer (getDocumentController());
}

juce::ARAAudioModification* ARA_DocumentSpecialisation::doCreateAudioModification(juce::ARAAudioSource *audioSource, ARA::ARAAudioModificationHostRef hostRef, const ARAAudioModification *optionalModificationToClone) noexcept
{
	return new ARA_AudioMod(audioSource, hostRef, optionalModificationToClone, undoManager);
}

juce::ARAPlaybackRegion* ARA_DocumentSpecialisation::doCreatePlaybackRegion(juce::ARAAudioModification *modification, ARA::ARAPlaybackRegionHostRef hostRef) noexcept
{
    return new ARA_PlaybackRegion(modification, hostRef);
}

bool ARA_DocumentSpecialisation::doRestoreObjectsFromStream (ARAInputStream& input,
								 const ARARestoreObjectsFilter* filter) noexcept
{
	ignoreUnused (input, filter);
	return false;
}

bool ARA_DocumentSpecialisation::doStoreObjectsToStream (ARAOutputStream& output, const ARAStoreObjectsFilter* filter) noexcept
{
	ignoreUnused (output, filter);
	return false;
}

//==============================================================================
// This creates the static ARAFactory instances for the plugin.
const ARA::ARAFactory* JUCE_CALLTYPE createARAFactory()
{
	return juce::ARADocumentControllerSpecialisation::createARAFactory<ARA_DocumentSpecialisation>();
}

juce::ARAPlaybackRegion* ARA_DocumentSpecialisation::getRegionAtIndex(int index)
{
    auto regionSequences = this->getDocumentController()->getDocument()->getRegionSequences();
    
    int indexToCheck = 0;
    for(auto sequence : regionSequences)
    {
        auto playbackRegions = sequence->getPlaybackRegions<juce::ARAPlaybackRegion>();
        for(auto* region : playbackRegions)
        {
            if(indexToCheck == index)
                return region;
            
            indexToCheck++;
        }
    }
        
    return nullptr;
}
