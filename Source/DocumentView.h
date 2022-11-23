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
#include "VerticalLayoutViewport.h"
#include "OverlayComponent.h"
#include "RegionSequenceView.h"
#include "TrackHeader.h"
#include "ZoomControls.h"

//==============================================================================
/*
*/
class DocumentView  : public juce::Component,
public juce::ChangeListener,
private juce::ARADocument::Listener,
private juce::ARAEditorView::Listener
{
public:
	explicit DocumentView (juce::ARADocument& document, PlayHeadState& playHeadState);

	~DocumentView() override;

    //==============================================================================
    // ARADocument::Listener overrides
	void didReorderRegionSequencesInDocument (juce::ARADocument*) override;

	void didAddRegionSequenceToDocument (juce::ARADocument*, juce::ARARegionSequence*) override;

	void willRemoveRegionSequenceFromDocument (juce::ARADocument*, juce::ARARegionSequence* regionSequence) override;

	void didEndEditing (juce::ARADocument*) override;

    //==============================================================================
	void changeListenerCallback (juce::ChangeBroadcaster*) override;

    //==============================================================================
    // ARAEditorView::Listener overrides
	void onNewSelection (const ARA::PlugIn::ViewSelection&) override;

	void onHideRegionSequences (const std::vector<juce::ARARegionSequence*>&) override;

    //==============================================================================
	void paint (juce::Graphics& g) override;

	void resized() override;

    //==============================================================================
	void setZoomLevel (double pixelPerSecond);

    static constexpr int headerWidth = 120;

private:
    struct RegionSequenceViewKey
    {
        explicit RegionSequenceViewKey (juce::ARARegionSequence* regionSequence)
            : orderIndex (regionSequence->getOrderIndex()), sequence (regionSequence)
        {
        }

        bool operator< (const RegionSequenceViewKey& other) const
        {
            return std::tie (orderIndex, sequence) < std::tie (other.orderIndex, other.sequence);
        }

        ARA::ARAInt32 orderIndex;
		juce::ARARegionSequence* sequence;
    };


	template <typename T>
	void layOutVertically (Rectangle<int> bounds, T& components, int verticalOffset = 0)
	{
		bounds = bounds.withY (bounds.getY() - verticalOffset).withHeight (bounds.getHeight() + verticalOffset);

		for (auto& component : components)
		{
			component.second->setBounds (bounds.removeFromTop (trackHeight));
			component.second->resized();
		}
	}
	
	void zoom (double factor);

	void update();

	void addTrackViews (juce::ARARegionSequence* regionSequence);

	void removeRegionSequenceView (juce::ARARegionSequence* regionSequence);

	void invalidateRegionSequenceViews();

	void rebuildRegionSequenceViews();



    static constexpr auto minimumZoom = 10.0;
    static constexpr auto trackHeight = 100;

	juce::ARADocument& araDocument;

    bool regionSequenceViewsAreValid = false;
    double timelineLength = 0;
    double zoomLevelPixelPerSecond = minimumZoom * 4;

    WaveformCache waveformCache;
    juce::Component tracksBackground;
	
    std::map<RegionSequenceViewKey, std::unique_ptr<TrackHeader>> trackHeaders;
    std::map<RegionSequenceViewKey, std::unique_ptr<RegionSequenceView>> regionSequenceViews;
    
	VerticalLayoutViewport viewport;
    OverlayComponent overlay;
    ZoomControls zoomControls;

    int viewportHeightOffset = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DocumentView)
};
