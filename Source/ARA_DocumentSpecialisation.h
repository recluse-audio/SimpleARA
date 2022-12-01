/*
  ==============================================================================

    ARAARA_PluginDocumentControllerSpecialisation.h
    Created: 2 Nov 2022 10:52:41am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class ARA_EditorRenderer;
class ARA_PlaybackRenderer;
class ARA_AudioMod;
class ARA_PlaybackRegion;


class ARA_DocumentSpecialisation  : public ARADocumentControllerSpecialisation
{
public:
	ARA_DocumentSpecialisation(const ARA::PlugIn::PlugInEntry* entry, const ARA::ARADocumentControllerHostInstance* instance);

protected:
	juce::ARAPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;

	juce::ARAEditorRenderer* doCreateEditorRenderer() noexcept override;
	
	juce::ARAAudioModification* doCreateAudioModification(juce::ARAAudioSource* audioSource,
												  ARA::ARAAudioModificationHostRef hostRef,
												  const juce::ARAAudioModification* optionalModificationToClone) noexcept override;
    
    juce::ARAPlaybackRegion* doCreatePlaybackRegion(juce::ARAAudioModification* modification,
                                                    ARA::ARAPlaybackRegionHostRef hostRef) noexcept override;

	bool doRestoreObjectsFromStream (ARAInputStream& input,
									 const ARARestoreObjectsFilter* filter) noexcept override;

	bool doStoreObjectsToStream (ARAOutputStream& output, const ARAStoreObjectsFilter* filter) noexcept override;
	
private:
};