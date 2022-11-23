/*
  ==============================================================================

    PossiblyBufferedReader.cpp
    Created: 2 Nov 2022 12:24:52pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "PossiblyBufferedReader.h"

PossiblyBufferedReader::PossiblyBufferedReader (std::unique_ptr<juce::BufferingAudioReader> readerIn)
	: setTimeoutFn ([ptr = readerIn.get()] (int ms) { ptr->setReadTimeout (ms); }),
	  reader (std::move (readerIn))
{
	
}

PossiblyBufferedReader::PossiblyBufferedReader (std::unique_ptr<juce::AudioFormatReader> readerIn)
	: setTimeoutFn(),
	  reader (std::move (readerIn))
{
	
}

void PossiblyBufferedReader::setReadTimeout (int ms)
{
	NullCheckedInvocation::invoke (setTimeoutFn, ms);
}

AudioFormatReader* PossiblyBufferedReader::get() const
{
	return reader.get();
	
}
