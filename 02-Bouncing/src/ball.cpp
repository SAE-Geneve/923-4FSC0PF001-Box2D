
#include <iostream>

#include "../include/ball.h"
#include "../include/game.h"

Ball::Ball(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{

}

void Ball::Init() {

    // Defining the shape
    shape_.setRadius(20.0f);
    shape_.setOrigin(shape_.getRadius(), shape_.getRadius());
    shape_.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = b2_dynamicBody;
    const b2Vec2 window_size = Game::PixelsToMeters(window_.getSize());
    body_def.position.Set(window_size.x / 2.0f, window_size.y / 2.0f);
    body_ = this->game_.GetWorld().CreateBody(&body_def);

    // Shape of the physical (A box)
    b2CircleShape ball_box;
    ball_box.m_radius = Game::PixelsToMeters(shape_.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &ball_box;
    player_fixture_def.density = 1.0f;
    player_fixture_def.friction = 0.0f;
    player_fixture_def.restitution = 0.6f; // Make it bounce a little bit

	player_fixture_def.userData.pointer = reinterpret_cast <std::uintptr_t>(this);

    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    auto fixture = body_->CreateFixture(&player_fixture_def);
    //body->SetUserData(this);

}

void Ball::Update() {
    
    //std::cout << "Ball position [" << body->GetPosition().x << ":" << body->GetPosition().y 
    //    << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    const b2Vec2 body_pos = body_->GetPosition();
    // Translate meters to pixels
    const sf::Vector2f graphic_position = Game::MetersToPixels(body_pos);
    // Set the position of the Graphic object
	shape_.setPosition(graphic_position);

}

void Ball::Render() const
{
	window_.draw(shape_);
}

void Ball::SetPixelsPosition(const sf::Vector2f pixels_position) const
{
    // Put in mouse position
    body_->SetTransform(Game::PixelsToMeters(pixels_position), body_->GetAngle());
    // Reset the velocity (Speed)
    body_->SetLinearVelocity(b2Vec2(0.0f, -0.00001f));
}

void Ball::SetNewColor()
{
	shape_.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}
