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
 */
class ZoomState
{
public:
	
	//====================
	ZoomState()
	{
		
	}
	//====================
	ZoomState(int pixelPerSecond, double pixelsPerRegion)
	{
		
	}
	
	//====================
	~ZoomState()
	{
		
	}
	
	//====================
	void setHorizontalZoom(double widthFactor)
	{
		mWidthFactor = jlimit ( minZoom, maxZoom, widthFactor);
	}
	
	//====================
	void setZoom(double widthFactor, double heightFactor)
	{
		
		mWidthFactor = jlimit ( minZoom, maxZoom, widthFactor);
		mHeightFactor = jlimit ( minZoom, maxZoom, heightFactor);
	}
	
	//====================
	int getPixelPerSecond() const
	{
		auto pixelPerSecond = basePixelPerSecond * mWidthFactor;
		jassert(pixelPerSecond >= minZoom * basePixelPerSecond);
		jassert(pixelPerSecond <= maxZoom * basePixelPerSecond);
		return pixelPerSecond;
	}
	
	//====================
	int getTrackHeight() const
	{
		return baseTrackHeight;
	}
	
private:
	static constexpr auto minZoom = 1.0;
	static constexpr auto maxZoom = 32.0;
	std::atomic<int> basePixelPerSecond { 10 };  // Atleast 10 pixels per second
	std::atomic<int> baseTrackHeight { 60 };  // Atleast 60 pixels per Region
	std::atomic<double> mWidthFactor  { minZoom };
	std::atomic<double> mHeightFactor { minZoom };
	
};
