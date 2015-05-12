
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "App.h"
#include "NetworkHandler.h"
#include "Server.h"

void* startNetwork(void* input) {
    NetworkHandler networkHandler(*(NetworkInterface*) input);
    while(true) {
        networkHandler.update();
    }
}

void* startServer(void* input) {
    Server server(*(ServerInterface*) input);
    while (true) {
        server.update();
    }
}

int main(int, char const**) {
    // Create the main window
    sf::VideoMode oneValidFullscreenMode = sf::VideoMode::getFullscreenModes()[0];
    sf::RenderWindow window(oneValidFullscreenMode, "SFML window", sf::Style::Fullscreen);
    window.setFramerateLimit(2);

    // Set the Icon
    sf::Image icon;
    if(!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    sf::Font font;
    if(!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return;
    }
    
    NetworkInterface networkInterface;
    networkInterface.receivedFromServer.push_back("TEST STRING ALPHA");
    networkInterface.sendToServer.push_back("TEST STRING BETA");
    
    ServerInterface serverInterface;
    
    App app = App(window, networkInterface);
    pthread_t networkThread;
    pthread_create(&networkThread, NULL, startNetwork, (void *)(&networkInterface));
    
    pthread_t serverThread;
    pthread_create(&serverThread, NULL, startServer, (void *)(&serverInterface));
    
    // Start the game loop
    while (window.isOpen()) {
        if(networkInterface.networkClosingStage == 2) {
            pthread_cancel(networkThread);
            window.close();
        }
        
        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Close window: exit
            if(event.type == sf::Event::Closed) {
                networkInterface.lock.lock();
                if(networkInterface.networkClosingStage == 0) {
                    networkInterface.networkClosingStage = 1;
                }
                networkInterface.lock.unlock();
            }
            else if(event.type == sf::Event::MouseMoved) {
                app.mouseMove(event.mouseMove);
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                app.mouseDown(event.mouseButton);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                app.mouseUp(event.mouseButton);
            }
            else if(event.type == sf::Event::KeyPressed) {
                app.keyDown(event.key);
            }
            else if(event.type == sf::Event::KeyReleased) {
                app.keyUp(event.key);
            }
            else if(event.type == sf::Event::TextEntered) {
                app.textEntered(event.text);
            }
        }
        
        app.think();

        // Clear screen
        window.clear();
        
        app.draw();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
