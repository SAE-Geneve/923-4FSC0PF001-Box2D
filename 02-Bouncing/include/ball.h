#pragma once

#include <limits>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball
{
public:
	Ball(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render() const;
	void SetPixelsPosition(sf::Vector2f pixels_position) const;

	void SetNewColor();

private:
	Game& game_;

	sf::CircleShape shape_;
	sf::RenderWindow& window_;
	b2Body* body_ = nullptr;

};
