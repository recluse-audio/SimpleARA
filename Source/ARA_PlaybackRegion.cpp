/*
  ==============================================================================

    ARA_PlaybackRegion.cpp
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_PlaybackRegion.h"

void ARA_PlaybackRegion::setCurrentlyInView(bool inView)
{
    currentlyInView = inView;
}

bool ARA_PlaybackRegion::isCurrentlyInView() const
{
    return currentlyInView;
}
