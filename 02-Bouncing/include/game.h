#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"
#include "box2d/b2_math.h"

#include "../include/ball.h"
#include "../include/bouncer.h"
#include "../include/contactListener.h"

class Game{
public:
	Game();
	void Init();
	void Loop();

	b2World& GetWorld() { return world_; };

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 PixelsToMeters(sf::Vector2u pixels);
	static float PixelsToMeters(float pixels);
	static sf::Vector2f MetersToPixels(b2Vec2 meters);

	static const float pixels_meters_ratio_;

private:

	// The window ---------------------------------------------
	sf::RenderWindow window_;

	// The physical world -------------------------------------
	b2Vec2 gravity_;
	b2World world_;

	Ball the_ball_;
	Bouncer bouncers_;

	ContactListener contact_listener_;

};
