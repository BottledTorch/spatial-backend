/*
  ==============================================================================

    MessageHandler.cpp
    Created: 27 Oct 2023 11:20:44am
    Author:  bultmanj

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MessageHandler.h"
#include <plibsys.h>
#include <iostream>

struct Message {
    int type;
    char msg[100];
};

MessageHandler::MessageHandler(TracktionCommands *tracktionCommands) {
    this->tracktionCommands = tracktionCommands;
}

MessageHandler::~MessageHandler() {

}

void MessageHandler::run()
{
    PSocketAddress* addr;
    PSocket* sock;
    p_libsys_init();


    if ((addr = p_socket_address_new("127.0.0.1", 5432)) == NULL) {
        DBG("Error opening socket");
    }

    if ((sock = p_socket_new(P_SOCKET_FAMILY_INET, P_SOCKET_TYPE_STREAM, P_SOCKET_PROTOCOL_TCP, NULL)) == NULL) {
        p_socket_address_free(addr);
        DBG("Error opening socket");
    }
    if (!p_socket_bind(sock, addr, FALSE, NULL)) {
        p_socket_address_free(addr);
        p_socket_free(sock);
        DBG("Error opening socket");
    }
    if (p_socket_listen(sock, NULL) == NULL) {
        DBG("Error trying to listen");
    }

    // TODO
    bool keepGoing = true;
    while (keepGoing) {
        DBG("Waiting for connection");
        PSocket* clientSocket = p_socket_accept(sock, NULL);
        if (clientSocket == NULL) {
            DBG("Error establishing connection");
            break;
        }

        DBG("Connection made");
        while (keepGoing) {
            struct Message message;
            int mSize = sizeof(message);
            memset((void*)&message, 0, sizeof(message));
            pchar* mAddr = (pchar*)&message;
            DBG("Waiting for data...");
            unsigned long long sizeOfMessage = -1;
            // pssize received = p_socket_receive(clientSocket, (pchar*)&sizeOfMessage, sizeof(sizeOfMessage), NULL);

            pssize size = p_socket_receive(clientSocket, mAddr, sizeof(message), NULL);
            if (size > 0) {
                if (message.type == 0) {
                    // Close connection
                    keepGoing = false;
                    break;
                }
                else if (message.type == 1) {
                    tracktionCommands->loadAudio("C:/Users/bultmanj/Downloads/Episode Titles - Copy/Episode Titles - mp3 files/EpisodeTitles/Audio Files/BrinkmanAdventuresEpisode_titles.1.wav");
                }
                else if (message.type == 2) {
                    tracktionCommands->playAudio();
                }
                else if (message.type == 3) {
                    tracktionCommands->stopAudio();
                }
                DBG(message.msg);
            }
            else {
                DBG("Error receiving data");
                break;
            }
        }

        // Close the client socket when communication is done
        p_socket_close(clientSocket, NULL);
        p_socket_free(clientSocket);
    }

    p_socket_address_free(addr);
    p_socket_close(sock, NULL);
    p_socket_free(sock);
    p_libsys_shutdown();
}
