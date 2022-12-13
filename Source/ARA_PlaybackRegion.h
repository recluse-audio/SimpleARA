/*
  ==============================================================================

    ARA_PlaybackRegion.h
    Created: 26 Nov 2022 12:15:41pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ARA_PlaybackRegion : public juce::ARAPlaybackRegion
{
public:
    using juce::ARAPlaybackRegion::ARAPlaybackRegion;
    void setCurrentlyInView(bool inView);
    bool isCurrentlyInView() const;
    
    
    /** This function takes the range of the start / end position of a process block
        and returns the range of an audio source should be read for this region given
        the timeline position of the process block
    */
    juce::Range<int64> getRangeToReadInAudioSource(juce::Range<int64> blockRange)
    {
        jassert(mSampleRate > 0);
        
        auto readRange = _getRangeOverlappingRegion(blockRange);
        
        if(readRange.isEmpty())
            return readRange; // save the calculation if
        
        readRange = _getRangeOverlappingAudioSource(readRange);
        
        return readRange;
    }
    
    
    /** How far into the */
    juce::int64 getModOffset() const
    {
        jassert(mSampleRate > 0);
        juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
        juce::Range<int64> modRange { getStartInAudioModificationSamples(), getEndInAudioModificationSamples() };
        
        const auto modOffset = getStartInAudioModificationSamples() - getStartInPlaybackSamples(mSampleRate);
        
        return modOffset;
    }


    
    void setSampleRate(double sampleRate)
    {
        mSampleRate = sampleRate;
    }
    
private:
    double mSampleRate = -1;
    bool currentlyInView = false;
    juce::Colour modColor;
    
    
    /** Pass this function a start / end sample position  and see where it overlaps with the bounds of this playback region
        Might be useful if you want to determine if you should render this region! ( start/end of a process buffer )
     */
    juce::Range<int64> _getRangeOverlappingRegion(juce::Range<int64> blockRange)
    {
        jassert(mSampleRate > 0);
        juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
        
        blockRange = blockRange.getIntersectionWith (regionRange);
        
        return blockRange;
    }
    
    
    /** Pass this function a start / end sample position  and see where it overlaps with the bounds of this playback region's full audio source duration
        Might be useful if you want to determine if you should render this region! ( start/end of a process buffer )
     */
    juce::Range<int64> _getRangeOverlappingAudioSource(juce::Range<int64> blockRange)
    {
        jassert(mSampleRate > 0);
        juce::Range<int64> regionRange  { getStartInPlaybackSamples(mSampleRate), getEndInPlaybackSamples(mSampleRate) };
        juce::Range<int64> modRange { getStartInAudioModificationSamples(), getEndInAudioModificationSamples() };
        
        blockRange = blockRange.getIntersectionWith (modRange.movedToStartAt (regionRange.getStart()));
        
        return blockRange;
    }
    
    
};
