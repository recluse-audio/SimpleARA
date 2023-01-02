/*
  ==============================================================================

    TrackData.h
    Created: 2 Jan 2023 11:17:56am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TrackData
{
public:
    TrackData()
    {
        
    }
    
    ~TrackData()
    {
        
    }
    
    void setSelected(bool isSelected)
    {
        currentlySelected = isSelected;
    }
    
    bool isCurrentlySelected() const
    {
        return currentlySelected;
    }
    
private:
    std::atomic<bool> currentlySelected { false };
}
