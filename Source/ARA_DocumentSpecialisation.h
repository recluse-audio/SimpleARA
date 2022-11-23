/*
  ==============================================================================

    ARAARA_PluginDocumentControllerSpecialisation.h
    Created: 2 Nov 2022 10:52:41am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ARA_EditorRenderer.h"
#include "ARA_PlaybackRenderer.h"
#include "ARA_AudioMod.h"

class ARA_AudioMod;
class CallbackTracker;

class ARA_DocumentSpecialisation  : public ARADocumentControllerSpecialisation
{
public:
	ARA_DocumentSpecialisation(const ARA::PlugIn::PlugInEntry* entry, const ARA::ARADocumentControllerHostInstance* instance);

protected:
	ARA_PlaybackRenderer* doCreatePlaybackRenderer() noexcept override;

	ARA_EditorRenderer* doCreateEditorRenderer() noexcept override;
	
	ARA_AudioMod* doCreateAudioModification(juce::ARAAudioSource* audioSource,
												  ARA::ARAAudioModificationHostRef hostRef,
												  const juce::ARAAudioModification* optionalModificationToClone) noexcept override;

	bool doRestoreObjectsFromStream (ARAInputStream& input,
									 const ARARestoreObjectsFilter* filter) noexcept override;

	bool doStoreObjectsToStream (ARAOutputStream& output, const ARAStoreObjectsFilter* filter) noexcept override;
	
	CallbackTracker& getCallbackTracker();
private:
	std::unique_ptr<CallbackTracker> callbackTracker;
};
