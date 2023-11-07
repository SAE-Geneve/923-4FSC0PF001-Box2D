#include "../include/game.h"

Game::Game() : gravity_(0.0f, 0.0f), world_(gravity_), the_ball_(this->window_)
{

}

void Game::Init() {

	world_.SetContactListener(&contact_listener_);

	window_.create(sf::VideoMode(1280, 720), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60.0f);

	// Init all elements
	the_ball_.Init(world_);

	// Add a bouncer
	// TOP LIMIT -------------------------------------------
	window_limits_.emplace_back(
		*this,
		sf::Vector2f(0.5f * window_.getSize().x, 0.0f),
		sf::Vector2f(window_.getSize().x, 10.0f)
	);
	// BOTTOM LIMIT -------------------------------------------
	window_limits_.emplace_back(
		*this,
		sf::Vector2f(0.5f * window_.getSize().x, window_.getSize().y),
		sf::Vector2f(window_.getSize().x, 10.0f)

	);
	// LEFT LIMIT -------------------------------------------
	window_limits_.emplace_back(
		*this,
		sf::Vector2f(0.0f, 0.5f * window_.getSize().y),
		sf::Vector2f(10.0F, window_.getSize().y)

	);
	// RIGHT LIMIT -------------------------------------------
	window_limits_.emplace_back(
		*this,
		sf::Vector2f(window_.getSize().x, 0.5f * window_.getSize().y),
		sf::Vector2f(10.0f, window_.getSize().y)

	);

}

void Game::Loop()
{

	while (window_.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (window_.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				window_.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = window_.getView();
				view.setSize(event.size.width, event.size.height);
				window_.setView(view);
			}

			// Mouse events ---------------------------------------------------------------------------------
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					//// mouse Released position detect
					mouse_pressed_pos_sensor_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					// mouse Released position detect
					mouse_pressed_pos_ball_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					//// mouse Released position detect
					mouse_released_pos_sensor_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

					sensors_.emplace_back(
						*this,
						this->window_,
						sf::Vector2f(
							0.5f * mouse_released_pos_sensor_.x + 0.5f * mouse_pressed_pos_sensor_.x,
							0.5f * mouse_released_pos_sensor_.y + 0.5f * mouse_pressed_pos_sensor_.y),
						0.5f * VecDistance(mouse_pressed_pos_sensor_, mouse_released_pos_sensor_)
					);
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouse_released_pos_ball_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					const sf::Vector2f velocity(mouse_released_pos_ball_.x - mouse_pressed_pos_ball_.x, mouse_released_pos_ball_.y - mouse_pressed_pos_ball_.y);

					the_ball_.SetPixelsPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), velocity);

					std::cout << "Ball velocity : " << the_ball_.GetLinearVelocity().x << " : " << the_ball_.GetLinearVelocity().y << " : " << the_ball_.GetLinearVelocity().Length() << std::endl;

				}

			}
			// Keyboard events
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					ClearBouncers();
				}
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
					the_ball_.Move(0, 0);
				}

			}
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Left) {
					the_ball_.Move(-1, 0);
				}
				if (event.key.code == sf::Keyboard::Right) {
					the_ball_.Move(1, 0);
				}
				if (event.key.code == sf::Keyboard::Up) {
					the_ball_.Move(0, 1);
				}
				if (event.key.code == sf::Keyboard::Down) {
					the_ball_.Move(0, -1);
				}

			}
		}
#pragma endregion


#pragma region Physical process
		// Updating the world with a delay
		elapsed_ = clock_.restart();
		world_.Step(elapsed_.asSeconds(), 6, 2);

		// Update the elements
		the_ball_.Update();
		for (auto& b : window_limits_) {
			b.Update();
		}
		for (auto& s : sensors_) {
			s.Update();
		}


#pragma endregion


#pragma region Graphics process
		// Clear all background
		window_.clear();

		// Render All elements
		window_.draw(the_ball_);
		for (auto& b : window_limits_) {
			window_.draw(b);
		}
		for (auto& s : sensors_) {
			window_.draw(s);
		}

		// Display all elements
		window_.display();
#pragma endregion

	}
}


void Game::ClearBouncers()
{

	for (std::vector<MySensor>::iterator s = sensors_.begin(); s != sensors_.end(); ++s)
	{
		// First remove bodies from the physical world
		world_.DestroyBody(s->GetBody());
		// Notice that the iterator is decremented after it is passed
		// to `erase()` but before `erase()` is executed
		//s = sensors.erase(s);
	}

	sensors_.clear();

}

