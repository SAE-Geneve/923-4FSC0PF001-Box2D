
#include <iostream>

#include "../include/bouncer.h"
#include "../include/game.h"

Bouncer::Bouncer(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{
}

void Bouncer::Init() {

    // Defining the shape
    // 2 meters long, 0,5 meters high
    const b2Vec2 physical_size(2.0f, 0.5f);
    shape_.setSize(sf::Vector2f(Game::MetersToPixels(physical_size)));
	shape_.setOrigin(0.5f * shape_.getSize());
	shape_.setFillColor(sf::Color::Cyan);
	
    // Defing the box 2D elements
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides

    const b2Vec2 window_size = Game::PixelsToMeters(sf::Vector2f(0.5f * window_.getSize().x, window_.getSize().y - 100.0f));
    body_def.position.Set(window_size.x, window_size.y);
    body_ = this->game_.GetWorld().CreateBody(&body_def);

    // Shape of the physical (A box)
    b2PolygonShape bouncer_box;
    bouncer_box.SetAsBox(physical_size.x / 2.0f, physical_size.y / 2.0f);

    // The fixture is what it defines the physic react
    b2FixtureDef player_fixture_def;
    player_fixture_def.shape = &bouncer_box;
    player_fixture_def.density = 1.0f;
    player_fixture_def.friction = 0.5f;
    player_fixture_def.restitution = 0.6f; // Make it bounce a little bit
    //playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
    body_->CreateFixture(&player_fixture_def);

}

void Bouncer::Update() {
    
    //std::cout << "Bouncer position [" << body->GetPosition().x << ":" << body->GetPosition().y 
    //    << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    const b2Vec2 body_pos = body_->GetPosition();
    // Translate meters to pixels
    const sf::Vector2f graphic_position = Game::MetersToPixels(body_pos);
    // Set the position of the Graphic object
	shape_.setPosition(graphic_position);

}

void Bouncer::Render() const
{
	window_.draw(shape_);
}

//void Bouncer::setPixelsPosition(sf::Vector2f _pixelsPosition) {
//    // Put in mouse position
//    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
//    // Reset the velocity (Speed)
//    body->SetLinearVelocity(b2Vec2_zero);
//}