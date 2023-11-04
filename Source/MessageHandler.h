/*
  ==============================================================================

    MessageHandler.h
    Created: 27 Oct 2023 11:20:44am
    Author:  bultmanj

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TracktionCommands.h"

//==============================================================================
/*
*/
class MessageHandler
{
public:
    MessageHandler(TracktionCommands *tracktionCommands);
    ~MessageHandler();
    void run();

private:
    TracktionCommands *tracktionCommands;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MessageHandler)
};
