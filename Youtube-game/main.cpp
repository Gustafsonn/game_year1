#include "SFML/Graphics.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Youtube Project");
	sf::Texture playertexture;
	playerTexture.loadFromFile("res/img/Player.png");
	sf::Sprite player(playerTexture);
	
	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(player);
		window.display();
	}
	
	return 0;
}