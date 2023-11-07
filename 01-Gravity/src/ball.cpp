
#include <iostream>

#include "../include/ball.h"
#include "../include/game.h"

Ball::Ball(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{
}

void Ball::Init() {

    // Defining the shape
	shape_.setRadius(Game::MetersToPixels(0.2f));
	shape_.setOrigin(sf::Vector2f(shape_.getRadius(), shape_.getRadius()));
	shape_.setFillColor(sf::Color::Red);
	shape_.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = Game::PixelsToMeters(window_.getSize());
    bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);
    body_ = this->game_.GetWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2CircleShape ballBox;
    ballBox.m_radius = Game::PixelsToMeters(shape_.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &ballBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body_->CreateFixture(&playerFixtureDef);

}

void Ball::Update() {
    
    std::cout << "body position [" << body_->GetPosition().x << ":" << body_->GetPosition().y 
        << "]|shape position [" << shape_.getPosition().x << ":" << shape_.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    b2Vec2 bodyPos = body_->GetPosition();
    // Translate meters to pixels
    sf::Vector2f graphicPosition = Game::MetersToPixels(bodyPos);
    // Set the position of the Graphic object
	shape_.setPosition(graphicPosition);

}

void Ball::Render() {
	window_.draw(shape_);
}

void Ball::SetPixelsPosition(sf::Vector2f pixels_position) {
    // Put in mouse position
    body_->SetTransform(Game::PixelsToMeters(pixels_position), body_->GetAngle());
    // Reset the velocity (Speed)
    body_->SetLinearVelocity(b2Vec2_zero);
}