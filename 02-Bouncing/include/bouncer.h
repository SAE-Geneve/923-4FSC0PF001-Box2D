#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer
{
public:
	explicit Bouncer(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render() const;

private:
	// Root game
	Game& game_;
	// Graphic object
	sf::RectangleShape shape_;
	// The SFMl Window
	sf::RenderWindow& window_;
	// The box 2D object
	b2Body* body_ = nullptr;

};
