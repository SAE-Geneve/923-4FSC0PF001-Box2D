#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer : public sf::Drawable
{
public:
	explicit Bouncer(Game& game, sf::Vector2f, sf::Vector2f);

	void Init(sf::Vector2f, sf::Vector2f);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	b2Body* GetBody() const { return body_; }

private:
	// Root game
	Game& game_;

	// Graphic object
	sf::RectangleShape shape_;
	sf::ConvexShape box_shape_;

	// The box 2D object
	b2Body* body_ = nullptr;

};
