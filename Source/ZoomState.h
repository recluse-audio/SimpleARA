/*
  ==============================================================================

    ZoomState.h
    Created: 18 Dec 2022 9:41:00am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

//=========================
/**
	This class is designed to be used by the Multi-track timeline object so its terms are set as such but this could be genericized easily
	
	This class changes as the zoom buttons are clicked, and then components update their state according to the zoom when they are good and ready
	
	Probably best if the MultiTrackTimeLine holds the instance of this and the TrackContentl/ Lanes/ etc. get a reference or use a getter function
	
	TO DO: Consider making this into a ChangeBroadcaster and the objects listeners
 */
class ZoomState 
{
public:
	
	//====================
	ZoomState()
	{
		
	}
	//====================
	ZoomState(int pixelsPerSecond, double pixelsPerRegion)
	{
		
	}
	
	//====================
	~ZoomState()
	{
		
	}
	
    //====================
    void setZoom(double widthFactor, double heightFactor)
    {
        setHorizontalZoom(widthFactor);
        mHeightFactor = jlimit ( minZoom, maxZoom, heightFactor);

    }
    
    //===================
    void increaseHorizontalZoom(double widthFactor)
    {
        mWidthFactor = jlimit ( minZoom, maxZoom, mWidthFactor * widthFactor);
        auto pixelsPerSecond = basePixelsPerSecond * mWidthFactor;
        this->_updatePixelsPerSecond(pixelsPerSecond);
    }
	
    //====================
    void setHorizontalZoom(double widthFactor)
    {
        mWidthFactor = jlimit ( minZoom, maxZoom, widthFactor);
        auto pixelsPerSecond = basePixelsPerSecond * mWidthFactor;
        this->_updatePixelsPerSecond(pixelsPerSecond);
    }

    
    //====================
    /** Zooms to show a duration in seconds over a width in pixels*/
    void zoomToShowDuration(double widthInPixels, double durationInSeconds)
    {
        this->_updatePixelsPerSecond(widthInPixels / durationInSeconds);
    }
	
    //====================
    /** Zooms to show a number of tracks over a height in pixels... this can be a fractional number of tracks*/
    void zoomToShowTracks(double heightInPixels, double numTracks)
    {
        this->_updateTrackHeight(heightInPixels / numTracks);
    }
    

    
	//====================
	int getPixelsPerSecond() const
	{
		return (int)currentPixelsPerSecond;
	}
    
	
	//====================
	int getTrackHeight() const
	{
		return (int)currentTrackHeight;
	}
    
    int getHeaderWidth() const
    {
        return baseHeaderWidth;
    }
	

    
    int getTimeRulerHeight() const
    {
        return baseTimeRulerHeight;
    }
    
    
    void copy(ZoomState& stateToCopy)
    {
        this->_updateTrackHeight(stateToCopy.getTrackHeight());
        this->_updatePixelsPerSecond(stateToCopy.getPixelsPerSecond());
    }
    
    
private:
	static constexpr auto minZoom = 1.0;
	static constexpr auto maxZoom = 32.0;
	std::atomic<double> mWidthFactor  { minZoom };
	std::atomic<double> mHeightFactor { minZoom };
    
    std::atomic<double> baseTrackHeight { 60.0 };  // Atleast 60 pixels per Region
    std::atomic<double> currentTrackHeight { 60.0 };

    std::atomic<double> basePixelsPerSecond { 10.0 };  // Atleast 10 pixels per second
    std::atomic<double> currentPixelsPerSecond { 10.0 };
    
    std::atomic<int> baseHeaderWidth { 60 }; // not really zoom related but shared in the same way... maybe don't put this here?
    std::atomic<int> baseTimeRulerHeight { 30 };
    
    //====================
    void _updatePixelsPerSecond(double pixPerSecond)
    {
        currentPixelsPerSecond = pixPerSecond;
        mWidthFactor = currentPixelsPerSecond / basePixelsPerSecond;
    }
    
    //====================
    
    void _updateTrackHeight(double trackHeight)
    {
        currentTrackHeight = trackHeight;
        mHeightFactor = currentTrackHeight / baseTrackHeight;
    }
};
