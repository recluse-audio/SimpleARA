/*
  ==============================================================================

    ARA_PlaybackRegion.h
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlaybackRegionView;

class ARA_PlaybackRegion : public juce::ARAPlaybackRegion
{
public:
    using juce::ARAPlaybackRegion::ARAPlaybackRegion;
    void setCurrentlyInView(bool inView);
    bool isCurrentlyInView() const;
    
	void setCurrentlySelected(bool isSelected);
	bool isCurrentlySelected() const;
	/**
		Returns the start and end of this playback region at its current position in the DAW timeline
		IF it were extended to the full duration of its audio source.
	 
		Becomes relevant when dealing with playback regions that have been trimmed
		Can return negative if full audio source would extend to before time 0.0 in the DAW timeline
	*/
	juce::Range<double> getFullRegionTimeRange();
	
	
    /** This function takes the range of the start / end position of a process block
        and returns the range of an audio source should be read for this region given
        the timeline position of the process block
    */
	juce::Range<int64> getRangeToReadInAudioSource(juce::Range<int64> blockRange);
    
    
    /** How far into the */
	juce::int64 getModOffset() const;


	void setSampleRate(double sampleRate);
    
	/** Full duration of this region's audio source*/
	double getAudioSourceDuration() const;
	
	
	
private:
    double mSampleRate = -1;
    bool currentlyInView = false;
	bool currentlySelected = false;
    juce::Colour modColor;
	
    
    
    /** Pass this function a start / end sample position  and see where it overlaps with the bounds of this playback region
        Might be useful if you want to determine if you should render this region! ( start/end of a process buffer )
     */
	juce::Range<int64> _getRangeOverlappingRegion(juce::Range<int64> blockRange);
    
    
    /** Pass this function a start / end sample position  and see where it overlaps with the bounds of this playback region's full audio source duration
        Might be useful if you want to determine if you should render this region! ( start/end of a process buffer )
     */
	juce::Range<int64> _getRangeOverlappingAudioSource(juce::Range<int64> blockRange);
    
};
