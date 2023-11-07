
#include <iostream>

#include "../include/bouncer.h"
#include "../include/game.h"
#include "../include/SFML_Utilities.h"

Bouncer::Bouncer(Game& game, const sf::Vector2f pos , const sf::Vector2f size) : game_(game)
{
    Init(pos, size);
}

void Bouncer::Init(const sf::Vector2f pos, const sf::Vector2f size) {

    // Defining the shape
    shape_.setSize(size);
	shape_.setFillColor(sf::Color::Cyan);
	shape_.setFillColor(sf::Color::Cyan);
    shape_.setOrigin(0.5F * shape_.getSize().x, 0.5F * shape_.getSize().y);
    shape_.setPosition(pos);
    //shape.setRotation(45.0f);

    // Defing the box 2D elements
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    body_def.position.Set(PixelsToMeters(shape_.getPosition()).x, PixelsToMeters(shape_.getPosition()).y);
    //float worldAngle = SFML_Utilities::vecAngle(Vector2f(1.0f, 0.0f), mouseLine);
    //bodyDef.angle = -1.0f * worldAngle;
    body_def.angle = 0.0f;
    body_ = this->game_.GetWorld().CreateBody(&body_def);

    //set this Ball object in the body's user data

    // Shape of the physical (A box)
    b2PolygonShape bouncer_box;
    //bouncerBox.SetAsBox(physicalSize.x, physicalSize.y);
    bouncer_box.SetAsBox(
        0.5f * PixelsToMeters(shape_.getSize()).x,
        0.5f * PixelsToMeters(shape_.getSize()).y,
        b2Vec2_zero,
        DegToRad(.0f));

    // The fixture is what it defines the physic react
    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &bouncer_box;
    player_fixture_def.density = 1.0f;
    player_fixture_def.friction = 0.2f;
    player_fixture_def.restitution = 0.6f; // Make it bounce a little bit
    body_->CreateFixture(&player_fixture_def);

}

void Bouncer::Update() {
    
    const auto& b2_position = body_->GetPosition();
    shape_.setPosition(MetersToPixels(b2_position));

    const auto b2_rotation = body_->GetAngle();
    shape_.setRotation(-1.0f * RadToDeg(b2_rotation));
    
}

void Bouncer::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{

    // You can draw other high-level objects
    target.draw(shape_, states);

}