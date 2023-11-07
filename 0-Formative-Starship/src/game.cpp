#include "game.h"

#include "data.h"
#include "RNG.h"

Game::Game() : _world(b2Vec2(0.0f, 0.0f))
{

	_window.create(sf::VideoMode(1080, 720), "The Game");

	// Basic Setup of the window
	// Vertical sync, framerate
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(30);

	_player = Player(_window.getSize(), _world);
	_gameOver = false;

	//font.loadFromFile("data/arial.ttf");
	text.setFont(Data::GetInstance().GlobalFont());
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(50, 250);

}

int Game::Loop()
{
	while (_window.isOpen())
	{

		CheckEvents();

		if (!_gameOver)
			Update();

		Draw();

	}

	return EXIT_SUCCESS;

}

void Game::Draw()
{
	// Graphical Region
	_window.clear(sf::Color::Black);

	_window.draw(_player);

	if(_gameOver)
	{
		text.setString("GAME OVER !");
		_window.draw(text);
	}

	// Window Display
	_window.display();
}

void Game::CheckEvents()
{
	// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
	sf::Event event;

	while (_window.pollEvent(event))
	{

		switch (event.type)
		{

			// évènement "fermeture demandée" : on ferme la fenêtre
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::MouseButtonPressed:
			_gameOver = false;
			system("cls");
			break;

		case sf::Event::KeyPressed:
			_manageKeyPressed(event.key.code);
			break;

		case sf::Event::KeyReleased:
			_manageKeyReleased(event.key.code);
			break;

		default:
			break;
		}

	}
}

void Game::_manageKeyPressed(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		_player.MoveLeft();
		break;

	case sf::Keyboard::Right:
		_player.MoveRight();
		break;

	default:
		break;
	}
}

void Game::_manageKeyReleased(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
	case sf::Keyboard::Right:
		_player.Stop();
		break;

	default:
		break;
	}
}

void Game::Update()
{
	const float timeElapsed = _clock.restart().asSeconds();

	_world.Step(timeElapsed, 8, 3);
	_player.Update(timeElapsed);

}

