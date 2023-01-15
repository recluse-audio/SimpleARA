/*
  ==============================================================================

    ZoomStateOwner.h
    Created: 10 Jan 2023 5:18:28pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include "ZoomState.h"

class ZoomStateOwner
{
public:
    ZoomStateOwner(ZoomState& state) : zoomState(state)
    {

    }
    
    ~ZoomStateOwner()
    {

    }
    

    
    void copyZoomState(ZoomState& newState)
    {
        zoomState.copy( newState );
        _updateZoomState();
    }
    
    ZoomState& getZoomState() const
    {
        return zoomState;
    }
    
protected:
    ZoomState& zoomState;
    
    /**
     ZoomStateOwners must actually do something when they should update so do that here
     */
    virtual void _updateZoomState() = 0;
};
