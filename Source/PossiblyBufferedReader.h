/*
  ==============================================================================

    PossiblyBufferedReader.h
    Created: 1 Nov 2022 12:45:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PossiblyBufferedReader
{
public:
    PossiblyBufferedReader() = default;

	explicit PossiblyBufferedReader (std::unique_ptr<juce::BufferingAudioReader> readerIn);

	explicit PossiblyBufferedReader (std::unique_ptr<juce::AudioFormatReader> readerIn);

	void setReadTimeout (int ms);

	juce::AudioFormatReader* get() const;

private:
    std::function<void (int)> setTimeoutFn;
    std::unique_ptr<juce::AudioFormatReader> reader;
};
