#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

float Length(const sf::Vector2f& rVector) {
	float fLength = sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
	return fLength;
}

sf::Vector2f Normalize(const sf::Vector2f& rVector) {
	float fLength = Length(rVector);
	sf::Vector2f vNormalizedVector(rVector.x / fLength, rVector.y / fLength);
	return vNormalizedVector;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Youtube Project");

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("res/img/Background.png");
	sf::Sprite background(backgroundTexture);
	
	sf::Texture playerTexture;
	playerTexture.loadFromFile("res/img/Player.png");
	sf::Sprite player(playerTexture);
	player.setScale(sf::Vector2f(10,10));
	player.setOrigin(sf::Vector2f(8,8));
	
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("res/img/Enemy.png");
	sf::Sprite enemy(enemyTexture);
	enemy.setScale(sf::Vector2f(10,10));
	enemy.setPosition(sf::Vector2f(960,540));
	enemy.setOrigin(sf::Vector2f(8,8));

	sf::Texture batonTexture;
	batonTexture.loadFromFile("res/img/Baton.png");
	sf::Sprite baton(batonTexture);
	baton.setScale(sf::Vector2f(10, 10));
	baton.setOrigin(sf::Vector2f(8, 8));

	sf::Clock clock;
	
	while (window.isOpen()) {

		sf::Time timeSinceLastFrame = clock.restart();

		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		sf::Vector2f vRequestedPlayerMovement(0.0f,0.0f);
		float fPlayerSpeed = 200.0f;
		// Player Movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			vRequestedPlayerMovement += sf::Vector2f(0.0f,-1.0f);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			vRequestedPlayerMovement += sf::Vector2f(1.0f,0.0f);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			vRequestedPlayerMovement += sf::Vector2f(0.0f,+1.0f);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			vRequestedPlayerMovement += sf::Vector2f(-1.0f,0.0f);
		}
		
		player.move(vRequestedPlayerMovement * timeSinceLastFrame.asSeconds() * fPlayerSpeed);

		sf::Vector2f vMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		sf::Vector2f vPlayerToMouse = vMousePosition - player.getPosition();
		sf::Vector2f vPlayerToMouseNormalized = Normalize(vPlayerToMouse);
		baton.setPosition(player.getPosition() + vPlayerToMouseNormalized*160.0f);

		//Did the baton hit the enemy?
		sf::Vector2f vBatonToEnemy = enemy.getPosition() - baton.getPosition();
		float fLengthFromBatonToEnemy = Length(vBatonToEnemy);

		if (fLengthFromBatonToEnemy < 160.0f) {
			//The Baton as it the enemy
			sf::Vector2f vNewPosition(std::rand() % 1920, std::rand() % 1080);
			enemy.setPosition(vNewPosition);
		}

		sf::Vector2f vEnemyToPlayer = player.getPosition() - enemy.getPosition();
		vEnemyToPlayer = Normalize(vEnemyToPlayer);
		float fEnemySpeed = 100.0f;

		enemy.move(vEnemyToPlayer * timeSinceLastFrame.asSeconds() * fEnemySpeed);
		 
		window.clear();
		window.draw(background);
		window.draw(enemy);
		window.draw(player);
		window.draw(baton);
		window.display();
	}
	
	return 0;
}