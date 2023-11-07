#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "ball.h"

class Game{
public:
	Game();
	void Init();
	void Loop();

	b2World& GetWorld() { return world_; }

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 PixelsToMeters(sf::Vector2u pixels);
	static float PixelsToMeters(float pixels);

	static sf::Vector2f MetersToPixels(b2Vec2 meters);
	static float MetersToPixels(float meters);

	static const float pixels_meters_ratio_;

private:

	// The window ---------------------------------------------
	sf::RenderWindow window_;

	// The physical world -------------------------------------
	b2World world_{ b2Vec2(0.0f, -9.81f) };

	Ball the_ball_;

};
