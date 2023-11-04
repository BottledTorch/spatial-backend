/*
  ==============================================================================

    TracktionCommands.cpp
    Created: 2 Nov 2023 3:26:07pm
    Author:  bultmanj

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TracktionCommands.h"

//==============================================================================
TracktionCommands::TracktionCommands()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TracktionCommands::~TracktionCommands()
{
}

int TracktionCommands::loadAudio(std::string path) {
    auto track = getAudioTracks(*defaultEdit)[0];

    juce::File file(path);
    AudioFile audioFile(engine, juce::File(path));

    track->insertWaveClip(file.getFileNameWithoutExtension(), file, { { {}, TimeDuration::fromSeconds(audioFile.getLength()) }, {} }, false);
    return 0;
}

int TracktionCommands::playAudio() {
    auto& transport = defaultEdit->getTransport();
    transport.setLoopRange({ 0_tp, defaultEdit->getLength() });
    transport.looping = true;
    transport.play(false);
    return 0;
}

int TracktionCommands::stopAudio() {
    auto& transport = defaultEdit->getTransport();
    transport.stop(false, false);
    return 0;
}

void TracktionCommands::initialise()
{
    defaultEdit = createEmptyEdit(engine, juce::File());
    defaultEdit->ensureNumberOfAudioTracks(1);
}
