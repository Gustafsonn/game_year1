//main.cpp
#include "game.h"
#include "ship.h"
#include <iostream>           // For std::cerr
#include <SFML/Graphics.hpp>  // For sf::Texture, sf::Sprite, sf::RenderWindow
//...
std::vector<Ship *> ships;

sf::Texture spritesheet;      // Texture to hold the spritesheet
sf::Sprite invader;           // Sprite for the invader
sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders"); // Main window

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
        return;
    }

    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32))); // Set sprite texture rectangle

    Invader* inv = new Invader(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)), sf::Vector2f{ 400,100 }, spritesheet);
    ships.push_back(inv);

    float invaderWidth = gameWidth / invaders_columns;
    float invaderHeight = gameHeight / invaders_rows;

    for (int r = 0; r < invaders_rows; ++r) {
        for (int c = 0; c < invaders_columns; ++c) {
            sf::Vector2f position(c * invaderWidth, r * invaderHeight);
            sf::IntRect rect(c * invaderWidth, r * invaderHeight, invaderWidth, invaderHeight); // Get the correct rectangle from spritesheet

            // Create an invader with the specific texture rect and position
            auto inv = new Invader(rect, position, spritesheet);
            ships.push_back(inv);
        }
    }
}

void Render() {
    window.clear();           // Clear the window
	    for (auto ship : ships) {
        window.draw(*ship); // Use dereference operator to draw each ship
    }
    window.display();      	// Display the drawn frame
}

int main() {
    Load(); // Load resources
    
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window when requested
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        Render(); // Call the render function to draw everything
    }

    // Clean up
    for (auto ship : ships) {
        delete ship; // Free allocated memory for each ship
    }

    return 0;
}
