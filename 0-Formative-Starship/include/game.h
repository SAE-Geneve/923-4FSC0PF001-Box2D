#pragma once
#include "player.h"

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

class Game
{
public:
	Game();

	void Draw();
	void CheckEvents();

	void Update();
	int Loop();

private:
	sf::RenderWindow _window;

	b2World _world;

	Player _player;

	sf::Font font;
	sf::Text text;

	//sf::Time _timeElapsed;
	sf::Clock _clock;

	bool _gameOver;

	void _manageKeyPressed(const sf::Keyboard::Key& key);
	void _manageKeyReleased(const sf::Keyboard::Key& key);


};
