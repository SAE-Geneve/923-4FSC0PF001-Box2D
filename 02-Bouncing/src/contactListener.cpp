
#include <iostream>
#include <box2d/b2_contact.h>

#include "../include/ball.h"
#include "../include/contactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin Contact" << std::endl;

	const auto user_data_a = contact->GetFixtureA()->GetUserData();
	const auto user_data_b = contact->GetFixtureB()->GetUserData();

	auto ball = reinterpret_cast<Ball*>(user_data_a.pointer);
	if(ball != nullptr)
	{
		std::cout << "A is a Ball." << std::endl;
		ball->SetNewColor();
	}

	ball = reinterpret_cast<Ball*>(user_data_b.pointer);
	if(ball != nullptr)
	{
		std::cout << "B is a Ball." << std::endl;
		ball->SetNewColor();
	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "End Contact" << std::endl;
}