#pragma once

#include "ContactEvent.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer
{

public:
	explicit Bouncer(Game& game_, sf::RenderWindow& window_);

	void init(b2Vec2 size, b2Vec2 position);
	void update();
	void render();
	void ContactReaction();

	std::string _name = "bouncer";

	bool valid_ = false;

	// The box 2D object
	b2Body* body_ = nullptr;


private:
	// Root game
	Game& game;
	// Graphic object
	sf::RectangleShape shape;
	// The SFMl Window
	sf::RenderWindow& window;


};
