/*
  ==============================================================================

    Zoomer.h
    Created: 13 Jan 2023 3:25:24pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include "ZoomState.h"

//======================
/**
    Class that holds a ref to a zoom state
    Inherit from this and override the pure virtual function
*/
class Zoomer
{
public:
    Zoomer(ZoomState& state) : mZoomState(state)
    {
    }
    
    ~Zoomer()
    {
        
    }
    
    virtual void updateZoomState() = 0;
    
private:
    ZoomState& mZoomState;
};
