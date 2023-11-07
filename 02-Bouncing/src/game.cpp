#include "../include/game.h"

const float Game::pixels_meters_ratio_ = 100.0f;

Game::Game() :
	gravity_(0, -9.81f),
	world_(gravity_),
	the_ball_(*this, this->window_),
	bouncers_(*this, this->window_)
{

}

void Game::Init() {

	window_.create(sf::VideoMode(1280, 720), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60.0f);

	// Init all elements
	the_ball_.Init();
	bouncers_.Init();

	world_.SetContactListener(&contact_listener_);
	
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
			if (event.type == sf::Event::MouseButtonReleased)
			{
				the_ball_.SetPixelsPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
		}
#pragma endregion


#pragma region Physical process
		// Updating the world with a delay
		constexpr float time_step = 1.0f / 60.0f;
		constexpr int32 velocity_iterations = 6;
		constexpr int32 position_iterations = 2;
		world_.Step(time_step, velocity_iterations, position_iterations);

		// Update the elements
		the_ball_.Update();
		bouncers_.Update();

#pragma endregion


#pragma region Graphics process
		// Clear all background
		window_.clear();
		// Render All elements
		the_ball_.Render();
		bouncers_.Render();
		// Display all elements
		window_.display();
#pragma endregion

	}
}

b2Vec2 Game::PixelsToMeters(sf::Vector2f pixels)
{
	return { pixels.x / pixels_meters_ratio_, -1.0f * pixels.y / pixels_meters_ratio_ };
}

b2Vec2 Game::PixelsToMeters(sf::Vector2u pixels)
{
	return {pixels.x / pixels_meters_ratio_, -1.0f * pixels.y / pixels_meters_ratio_};
}

float Game::PixelsToMeters(float pixels)
{
	return pixels / pixels_meters_ratio_;
}

sf::Vector2f Game::MetersToPixels(b2Vec2 meters)
{
	return {meters.x * pixels_meters_ratio_, -1.0f * meters.y * pixels_meters_ratio_};
}

