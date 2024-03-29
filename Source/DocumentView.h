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
#include "ARAView.h"

class SimpleARAEditor;
class WaveformCache;
class ZoomState;
class PlayheadOverlay;
class PlayheadMarker;
class TimeGrid;
class RegionSequenceView;
class ZoomControls;
class ARAViewSection;
class SequenceHeader;
//==============================================================================
/*
    This class is for the timeline and can scroll horizontally and vertically.  
*/
class DocumentView  : public juce::Component,
public juce::ChangeListener
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
    
	void addRegionSequence(juce::ARARegionSequence* newSequence);
    
    void updateZoomState(); // rename this to update size?
	
	double getDuration() const;
	
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
	ARAViewSection& araSection;
	ZoomState& zoomState;
	juce::ARADocument& araDocument;
	
    std::unique_ptr<TimeGrid> timeGrid;
    std::unique_ptr<PlayheadMarker> playheadMarker;
    
	juce::OwnedArray<RegionSequenceView> sequenceViews;
	juce::OwnedArray<SequenceHeader> sequenceHeaders;

	
    double playheadPos = 0.0;
    
    /** Get duration of longest region sequence */
    double _getMaxDuration() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DocumentView)
};
