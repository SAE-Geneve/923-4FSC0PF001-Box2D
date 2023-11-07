#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "SFML_Utilities.h"

#include "ball.h"
#include "bouncer.h"
#include "contact_listener.h"
#include "mySensor.h"
#include "user_data.h"


class Game{
public:
	Game();
	void Init();
	void Loop();

	b2World& GetWorld() { return world_; }

private:

	// The window ---------------------------------------------
	sf::RenderWindow window_;

	// The physical world -------------------------------------
	b2Vec2 gravity_;
	b2World world_;
	MyContactListener contact_listener_;

	Ball the_ball_;
	std::vector<Bouncer> window_limits_;
	std::vector<MySensor> sensors_;

	void ClearBouncers();

	sf::Vector2f mouse_pressed_pos_sensor_, mouse_released_pos_sensor_;
	sf::Vector2f mouse_pressed_pos_ball_, mouse_released_pos_ball_;

	sf::Time elapsed_;
	sf::Clock clock_;

};
