# SimpleARA

Simple ARA is an in progress ARA project meant to be simple.  

The goal is to demonstrate basic ARA functionality and to provide a jumping off point for future ARA projects.

To maintain correct releases of JUCE / ARA, this repository keeps the JUCE and the ARA_SDK repos as submodules

## Versions 
JUCE      7.0.3 

ARA_SDK   2.1.0

## Installing
After cloning this repository, cd into it.  Update the ARA and JUCE submodules using

`git submodule update --init --recursive`

If after this step the ARA_SDK folders have not been populated and are empty, you may need to call the same 

`git submodule update --init --recursive`

from within the ARA_SDK

## Projucer
It is best to build the projucer for your targeted platform by building the executable from within the JUCE submodule.

*Located here*

*SimpleARA/JUCE/extras/Projucer/Builds*

See the [JUCE readme](https://github.com/juce-framework/JUCE) for more details
