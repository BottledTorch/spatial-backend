/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"
#include <thread>
#include "MessageHandler.h"

//==============================================================================
class Spatial  : public juce::JUCEApplicationBase
{
public:
    //==============================================================================
    Spatial() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        tracktionCommands = new TracktionCommands();
        tracktionCommands->initialise();
        tracktionCommands->loadAudio("C:/Users/bultmanj/Downloads/Episode Titles - Copy/Episode Titles - mp3 files/EpisodeTitles/Audio Files/BrinkmanAdventuresEpisode_titles.1.wav");
        
        messageHandler = new MessageHandler(tracktionCommands);
        messageHandler->run();
        // std::thread messageThread(&MessageHandler::run, messageHandler);

        // This method is where you should put your application's initialisation code..
        // playAudio("C:/Users/bultmanj/Downloads/Episode Titles - Copy/Episode Titles - mp3 files/EpisodeTitles/Audio Files/BrinkmanAdventuresEpisode_titles.1.wav");

    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

private:

    TracktionCommands *tracktionCommands;
    MessageHandler *messageHandler;

    // Inherited via JUCEApplicationBase
    void suspended() override
    {
    }
    void resumed() override
    {
    }
    void unhandledException(const std::exception*, const juce::String& sourceFilename, int lineNumber) override
    {
    }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (Spatial)
