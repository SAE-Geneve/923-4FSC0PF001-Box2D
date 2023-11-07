#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class Game;

class MySensor : public sf::Drawable
{
public:
	explicit MySensor(Game& game, sf::RenderWindow& window, sf::Vector2f pos, int radius);

	void Init(sf::Vector2f pos, int radius);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	b2Body* GetBody() const { return body_; }
	void SetColor(sf::Color color);

private:
	// Root game
	Game& game_;
	// Graphic object
	sf::CircleShape shape_;
	// The box 2D object
	b2Body* body_ = nullptr;

};
