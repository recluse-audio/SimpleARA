/*
  ==============================================================================

    RegionData.h
    Created: 2 Jan 2023 11:18:36am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RegionData
{
public:
    RegionData()
    {
        
    }
    
    ~RegionData()
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
