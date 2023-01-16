/*
  ==============================================================================

    DocumentView.h
    Created: 1 Nov 2022 12:50:54pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UtilObjects.h"

class SimpleARAEditor;
class WaveformCache;
class ZoomState;
class PlayheadOverlay;
class PlayheadMarker;
class TimeGrid;
class RegionSequenceView;
class ZoomControls;
class ARAViewSection;
//==============================================================================
/*
    This class is for the timeline and can scroll horizontally and vertically.  
*/
class DocumentView  : public juce::Component
{
public:
	DocumentView (ARAViewSection& viewSection, juce::ARADocument& document);

	~DocumentView() override;

    //==============================================================================
	void paint (juce::Graphics& g) override;

	void resized() override;

    //==============================================================================
    void updateViewSelection();
    void updatePlayheadPosition(double positionInSeconds);
    
    void clear();
    
    void addRegionSequence(juce::ARARegionSequence* newSequence)
    {
        //regionSequences.add(newSequence);
    }
    
    void updateZoomState();

private:
    ARAViewSection& araSection;
	juce::ARADocument& araDocument;
    ZoomState& zoomState;
	
    std::unique_ptr<TimeGrid> timeGrid;
    std::unique_ptr<PlayheadMarker> playheadMarker;
    

    juce::OwnedArray<RegionSequenceView> regionSequences;
    
    double playheadPos = 0.0;
    
    /** Get duration of longest region sequence */
    double _getMaxDuration() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DocumentView)
};
