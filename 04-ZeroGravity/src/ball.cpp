
#include <iostream>

#include "../include/ball.h"
#include "../include/game.h"

Ball::Ball(sf::RenderWindow& window) : window_(window)
{
}

void Ball::Init(b2World& world) {

    // Defining the shape
	shape_.setRadius(20.0f);
    shape_.setOrigin(shape_.getRadius(), shape_.getRadius());
	shape_.setFillColor(sf::Color::Red);
	shape_.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = b2_dynamicBody;
    body_def.linearDamping = 0.5f;

    const b2Vec2 window_size = PixelsToMeters(window_.getSize());
    body_def.position.Set(window_size.x / 2.0f, window_size.y / 2.0f);
    body_ = world.CreateBody(&body_def);

    // Shape of the physical (A box)
    b2CircleShape ball_box;
    ball_box.m_radius = PixelsToMeters(shape_.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef ball_fixture_def;
    ball_fixture_def.shape = &ball_box;
    ball_fixture_def.density = 1.0f;
    ball_fixture_def.friction = 10.0f;
    ball_fixture_def.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body_->CreateFixture(&ball_fixture_def);

}

void Ball::Update() {
    
    // Get the position of the body
    const b2Vec2 body_pos = body_->GetPosition();

    // Translate meters to pixels
    const sf::Vector2f graphic_position = MetersToPixels(body_pos);

    // Set the position of the Graphic object
	shape_.setPosition(graphic_position);

}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // You can draw other high-level objects
    target.draw(shape_, states);

}

void Ball::SetPixelsPosition(const sf::Vector2f pixels_position, const sf::Vector2f velocity) const
{
	constexpr float kMagicNumber = 3.0f;

    // Put in mouse position
    body_->SetTransform(PixelsToMeters(pixels_position), body_->GetAngle());
    // Reset the velocity (Speed)
    const b2Vec2 newb2_velocity = PixelsToMeters(sf::Vector2f(kMagicNumber * velocity.x, kMagicNumber * velocity.y));
    //b2Vec2 newb2Velocity(velocity_.x, velocity_.y);
    body_->SetLinearVelocity(newb2_velocity);
}

void Ball::Move(const float x, const float y) const
{
    // Set forces -------------------------------------------------
    body_->ApplyForceToCenter(b2Vec2(x, y * -1.f), true);

}
