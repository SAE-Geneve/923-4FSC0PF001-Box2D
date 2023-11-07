
#include <iostream>
#include <math.h>

#include "../include/mySensor.h"
#include "../include/game.h"
#include "../include/SFML_Utilities.h"

MySensor::MySensor(Game& game, sf::RenderWindow& window, sf::Vector2f pos, int radius) : game_(game)
{
    Init(pos, radius);
}

void MySensor::Init(const sf::Vector2f pos, const int radius) {

    // Defining the shape
    shape_.setPosition(pos);
    shape_.setOrigin(radius, radius);
    shape_.setRadius(radius);
	shape_.setFillColor(sf::Color::Cyan);

    // Defing the box 2D elements
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    body_def.position.Set(PixelsToMeters(shape_.getPosition()).x, PixelsToMeters(shape_.getPosition()).y);
    body_def.angle = 0.0f;
    body_ = this->game_.GetWorld().CreateBody(&body_def);

    // Shape of the physical (A box)
    b2CircleShape shape_box;
    shape_box.m_radius = PixelsToMeters(shape_.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &shape_box;
    player_fixture_def.density = 1.0f;
    player_fixture_def.friction = 0.2f;
    player_fixture_def.restitution = 0.6f; // Make it bounce a little bit
    player_fixture_def.userData.pointer = reinterpret_cast <std::uintptr_t>(this);
    body_->CreateFixture(&player_fixture_def);

}

void MySensor::Update() {

    const auto& b2_position = body_->GetPosition();
    shape_.setPosition(MetersToPixels(b2_position));

    const auto b2_rotation = body_->GetAngle();
    shape_.setRotation(-1.0f * RadToDeg(b2_rotation));

}

void MySensor::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(shape_, states);
}

void MySensor::SetColor(const sf::Color color)
{
    shape_.setFillColor(color);
}
