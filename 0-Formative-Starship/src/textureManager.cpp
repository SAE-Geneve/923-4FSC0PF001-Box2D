#include "textureManager.h"

TextureManager::TextureManager()
{
	m_asteroidTexture.loadFromFile("./data/Asteroid.png");
	m_shipTexture.loadFromFile("./data/Ship.png");
	m_gameOverTexture.loadFromFile("./data/GameOver.png");
	m_missileTexture.loadFromFile("./data/missile.png");
}

sf::Texture TextureManager::GetAsteroidTexture()
{
	return m_asteroidTexture;
}