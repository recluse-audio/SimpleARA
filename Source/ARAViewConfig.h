/*
  ==============================================================================

    ARAViewConfig.h
    Created: 31 Jan 2023 5:31:37pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

/**
	A class that holds the configurations of an ARAViewSection.  Set Values like minNumberOfLanes and so on
 */

class ARAViewConfig
{
public:
	ARAViewConfig(){};
	~ARAViewConfig(){};
	
private:
	int minNumberOfLanes = 12; //
}
