/*
  ==============================================================================

	ARA_DocumentController.cpp
    Created: 2 Nov 2022 10:55:15am
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_DocumentSpecialisation.h"
#include "CallbackTracker.h"

ARA_DocumentSpecialisation::ARA_DocumentSpecialisation(const ARA::PlugIn::PlugInEntry* entry, const ARA::ARADocumentControllerHostInstance* instance)
: juce::ARADocumentControllerSpecialisation(entry, instance)
{
	callbackTracker = std::make_unique<CallbackTracker>();
}

ARA_PlaybackRenderer* ARA_DocumentSpecialisation::doCreatePlaybackRenderer() noexcept
{
	return new ARA_PlaybackRenderer (getDocumentController());
}

ARA_EditorRenderer* ARA_DocumentSpecialisation::doCreateEditorRenderer() noexcept
{
	return new ARA_EditorRenderer (getDocumentController());
}

ARA_AudioMod* ARA_DocumentSpecialisation::doCreateAudioModification(juce::ARAAudioSource *audioSource, ARA::ARAAudioModificationHostRef hostRef, const ARAAudioModification *optionalModificationToClone) noexcept
{
	return new ARA_AudioMod(audioSource, hostRef, optionalModificationToClone);
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
