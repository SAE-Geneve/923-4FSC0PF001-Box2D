
#pragma once

#include <string>

#include "SFML/Graphics.hpp"

class TextureManager
{
private:

    sf::Texture m_asteroidTexture;
    sf::Texture m_shipTexture;
    sf::Texture m_gameOverTexture;
    sf::Texture m_missileTexture;

public:

    TextureManager();
	
    // --------------------
    // Getters
    sf::Texture& getAsteroidTexture();
    sf::Texture& getShipTexture();
    sf::Texture& getGameOverTexture();
    sf::Texture& getMissileTexture();


};


