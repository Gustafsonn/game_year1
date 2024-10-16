#include "SFML/Graphics.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Youtube Project");
	
	sf::Texture playerTexture;
	playerTexture.loadFromFile("res/img/Player.png");
	sf::Sprite player(playerTexture);
	
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("res/img/Enemy.png");
	sf::Sprite enemy(enemyTexture);
	
	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.display();
	}
	
	return 0;
}