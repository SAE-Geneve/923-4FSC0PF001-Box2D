#pragma once

#include <limits>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball : public sf::Drawable
{
public:
	Ball(sf::Vector2f pixelPos, Game& game_);
	~Ball() override;

	Ball& operator=(const Ball& other);

	//void init(sf::RenderWindow& window);
	void update();

	void setPixelsPosition(sf::Vector2f _pixelsPosition);

	void SetNewColor(sf::Color color);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void ContactReaction();
	void SetDead(bool dead);
	bool IsDead() { return _isDead; }

	std::string _name = "ball";

	bool valid_ = false;

	b2Body* body_ = nullptr;

private:
	Game& _game;
	bool _isDead = true;

protected:
	sf::CircleShape _shape;

};
