/*
  ==============================================================================

    ZoomState.h
    Created: 18 Dec 2022 9:41:00am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ARAViewSection.h"

//=========================
/**
	This class is designed to be used by the Multi-track timeline object so its terms are set as such but this could be genericized easily
	
	This class changes as the zoom buttons are clicked, and then components update their state according to the zoom when they are good and ready
	
	Probably best if the MultiTrackTimeLine holds the instance of this and the TrackContentl/ Lanes/ etc. get a reference or use a getter function
	
	TO DO: Consider making this into a ChangeBroadcaster and the objects listeners
 */
class ZoomState : public juce::ChangeBroadcaster
{
public:
	
	//====================
	ZoomState(ARAViewSection& section) : araSection(section)
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
	// Passing 0.1 will increase horizontal zoom by 10%.  10% more pixels per second
	// passing -0.1 will decrease horizontal zoom by 10%   10% fewer pixels per second
    void transformHorizontalZoomByPercent(double widthTransformPercent)
    {
		auto transformedWidthFactor = mWidthFactor * ( 1.0 + widthTransformPercent );
		
        mWidthFactor = jlimit ( minZoom, maxZoom, transformedWidthFactor);
		
        auto pixelsPerSecond = basePixelsPerSecond * mWidthFactor;
		
        this->_updatePixelsPerSecond(pixelsPerSecond);
    }
	
	//====================
	void transformVerticalZoomByPercent(double transformPercent)
	{
		auto transformedHeightFactor = mHeightFactor * ( 1.0 + transformPercent );
		
		mHeightFactor = jlimit ( minZoom, maxZoom, transformedHeightFactor);
		
		auto trackHeight = baseTrackHeight * mHeightFactor;
		
		this->_updateTrackHeight(trackHeight);
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
    

	void copy(ZoomState& stateToCopy)
	{
		this->_updateTrackHeight(stateToCopy.getTrackHeight());
		this->_updatePixelsPerSecond(stateToCopy.getPixelsPerSecond());
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
    
    int getRegionHeight() const
	{
		return getTrackHeight() - (regionOutlineWidth * 2.0);
	}
	
	int getRegionOutlineWidth() const
	{
		return (int)regionOutlineWidth;
	}

	/** Sends an updateZoomState() change broadcast to all listeners */
	void triggerUpdate()
	{
		// get old view position and calculate proportionally
		auto viewport = araSection.getDocumentViewport();
		auto contentSize = viewport->getViewedComponent()->getLocalBounds();
		auto viewPosition = viewport->getViewPosition();
		auto proportionX = (double) viewPosition.getX() / (double) contentSize.getWidth();
		auto proportionY = (double) viewPosition.getY() / (double) contentSize.getHeight();
		
		sendSynchronousChangeMessage();
		
		// apply same
		auto newSize = viewport->getViewedComponent()->getLocalBounds();
		auto newX = (double) newSize.getWidth() * proportionX;
		auto newY = (double) newSize.getHeight() * proportionY;
		viewport->setViewPosition(newX, newY);
		//viewport->setViewPositionProportionately((double) newX, (double) proportionY);
	}
	

    
private:
	ARAViewSection& araSection;
	static constexpr auto minZoom = 1.0;
	static constexpr auto maxZoom = 32.0;
	static constexpr auto regionOutlineWidth = 1.0; // num pixels outlining each region
	std::atomic<double> mWidthFactor  { minZoom };
	std::atomic<double> mHeightFactor { minZoom };
    
    std::atomic<double> baseTrackHeight { 60.0 };  // Atleast 60 pixels per Region
    std::atomic<double> currentTrackHeight { 60.0 };

    std::atomic<double> basePixelsPerSecond { 10.0 };  // Atleast 10 pixels per second
    std::atomic<double> currentPixelsPerSecond { 10.0 };
    
    std::atomic<int> baseHeaderWidth { 90 }; // not really zoom related but shared in the same way... maybe don't put this here?
    std::atomic<int> baseTimeRulerHeight { 30 };
    
	float relativeViewX = 0.f, relativeViewY = 0.f;
	
    //====================
    void _updatePixelsPerSecond(double pixPerSecond)
    {
        currentPixelsPerSecond = pixPerSecond;
        mWidthFactor = currentPixelsPerSecond / basePixelsPerSecond;
		triggerUpdate();
    }
    
    //====================
    
    void _updateTrackHeight(double trackHeight)
    {
        currentTrackHeight = trackHeight;
        mHeightFactor = currentTrackHeight / baseTrackHeight;
		triggerUpdate();
    }
};
