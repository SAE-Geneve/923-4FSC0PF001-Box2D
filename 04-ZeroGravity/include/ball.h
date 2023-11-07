#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	explicit Ball(sf::RenderWindow& window);

	void Init(b2World& world);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetPixelsPosition(sf::Vector2f pixels_position, sf::Vector2f velocity) const;

	b2Vec2 GetLinearVelocity() const
	{
		return body_->GetLinearVelocity();
	}

	void Move(float x, float y) const;

private:
	sf::CircleShape shape_;
	sf::RenderWindow& window_;
	
	b2Body* body_ = nullptr;

};
