/*
  ==============================================================================

    AudioMod_UndoAction.h
    Created: 10 Dec 2022 3:59:29pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AudioMod_UndoAction : public juce::UndoableAction
{
public:
    AudioMod_UndoAction(juce::AudioProcessorParameter* param, float normOldValue, float normNewValue )
    : pParameter(param)
    , mNormalizedOldValue(normOldValue)
    , mNormalizedNewValue(normNewValue)
    {
        
    }
    
    ~AudioMod_UndoAction()
    {
        delete pParameter;
    }
    
    bool perform() override
    {
        pParameter->setValue(mNormalizedNewValue);
        return true;
    }
    
    bool undo() override
    {
        pParameter->setValue(mNormalizedOldValue);
        return true;
    }
    
private:
    juce::AudioProcessorParameter* pParameter;
    float mNormalizedOldValue;
    float mNormalizedNewValue;
};


