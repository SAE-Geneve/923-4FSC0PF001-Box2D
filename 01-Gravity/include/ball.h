#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball
{
public:
	explicit Ball(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render();
	void SetPixelsPosition(sf::Vector2f pixels_position);

private:
	Game& game_;

	sf::CircleShape shape_;
	sf::RenderWindow& window_;
	b2Body* body_ = nullptr;

};
