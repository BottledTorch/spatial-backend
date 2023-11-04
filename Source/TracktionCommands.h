/*
  ==============================================================================

    TracktionCommands.h
    Created: 2 Nov 2023 3:26:07pm
    Author:  bultmanj

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


using namespace tracktion;


//==============================================================================
/*
*/
class TracktionCommands
{
public:
    TracktionCommands();
    ~TracktionCommands();

    int loadAudio(std::string path);


    int playAudio();
    int stopAudio();
    void initialise();

private:
    Engine engine{ "Spatial" };
    std::unique_ptr<Edit> defaultEdit;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TracktionCommands)
};
