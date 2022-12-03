/*
  ==============================================================================

    NavigationMenu.cpp
    Created: 2 Dec 2022 7:29:37pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NavigationMenu.h"

//==============================================================================
NavigationMenu::NavigationMenu(juce::ARADocument& document) : araDocument(document)
{
    menuButton = std::make_unique<juce::TextButton>("ARA OBJECTS");
    menuButton->addListener(this);
    menuButton->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    addAndMakeVisible(menuButton.get());

    popupMenu = std::make_unique<juce::PopupMenu>();
    _prepareMenu();
}

NavigationMenu::~NavigationMenu()
{
}

void NavigationMenu::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::deeppink);
}

void NavigationMenu::resized()
{
    menuButton->setBoundsRelative(0.f, 0.f, 1.f, 1.f);

}

void NavigationMenu::buttonClicked(juce::Button *b)
{
    if (b == menuButton.get())
    {
        _prepareMenu();
        auto menuArea = Rectangle<int>(getScreenX(), getScreenY() - getParentHeight(), getParentWidth(), getParentHeight());
        
        popupMenu->showMenuAsync(PopupMenu::Options().withTargetScreenArea(menuArea),
       [this](int action)
       {
           if (action == 0)
           {
               popupMenu->dismissAllActiveMenus();
           }
           else if (action >= 1)
           {
               popupMenu->dismissAllActiveMenus();

           }
   
       });
    }
    repaint();
}

void NavigationMenu::_prepareMenu()
{
    popupMenu->clear();
    popupMenu->addSectionHeader("Region Sequences");
    popupMenu->addSeparator();

    auto regionSequences = araDocument.getRegionSequences();
    for(size_t index = 0; index < regionSequences.size(); index++)
    {
        auto regionSequence = regionSequences[index];
        auto sequenceMenu = _makeRegionSequenceMenu(regionSequence);
        auto sequenceName = juce::String(regionSequence->getName());
        popupMenu->addSubMenu(sequenceName, *sequenceMenu);

    }
    
   // int itemIndex = 1; // used to properly index artist romples without resetting in the artist loop

//    for (int artistIndex = 0; artistIndex < database.artists.size(); artistIndex++) // Artists - just a section header
//    {
//        auto artist = database.artists[artistIndex];
//        popupMenu->addSectionHeader(artist->getArtistName());
//
//        for (int categoryIndex = 0; categoryIndex < artist->getNumCategories(); categoryIndex++)
//        {
//
//            auto categoryMenu = new PopupMenu();
//            auto category = artist->getCategory(categoryIndex);
//            auto romples = category.getRompleArray();
//
//            for (int rompleIndex = 0; rompleIndex < romples.size(); rompleIndex++)
//            {
//                categoryMenu->addItem(itemIndex, romples[rompleIndex]); // item index keeps track of the different categories
//                itemIndex++;
//            }
//
//            menu.addSubMenu(category.getName(), *categoryMenu);
//        }
//
//    }

    
}

juce::PopupMenu* NavigationMenu::_makeRegionSequenceMenu(juce::ARARegionSequence* regionSequence)
{
    auto regionSequenceMenu = new juce::PopupMenu();
    
    regionSequenceMenu->addSectionHeader(juce::String(regionSequence->getName()));
    
    const auto& regions = regionSequence->getPlaybackRegions();
    
    for(size_t index = 0; index < regions.size(); index++)
    {
        auto regionName = juce::String(regions[index]->getName());
        regionSequenceMenu->addItem(index + 1, regionName);
    }
    
    return regionSequenceMenu;
}
