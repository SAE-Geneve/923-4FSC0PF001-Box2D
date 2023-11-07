#include "../include/contactListener.h"
#include "../include/contactEvent.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "../include/ball.h"
#include "../include/bouncer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin Contact" << std::endl;

	auto userDataA = contact->GetFixtureA()->GetUserData().pointer;
	auto userDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (userDataA != 0 && userDataB != 0)
	{
		// Is the first object a ball ?
		auto ball_collider = reinterpret_cast<ContactEvent<Ball, ContactType::Ball>*>(userDataA);
		auto bouncer_collider = reinterpret_cast<ContactEvent<Bouncer, ContactType::Bouncer>*>(userDataB);

		if (ball_collider->TypeOfContact == ContactType::Ball && bouncer_collider->TypeOfContact == ContactType::Bouncer) {

			std::cout << "A is a ball, B a limit" << " names : " << ball_collider->ObjPtr->_name << ":" << bouncer_collider->ObjPtr->_name << std::endl;

			if (ball_collider->TypeOfContact == ContactType::Ball && ball_collider->ObjPtr->valid_ == true)
				ball_collider->ObjPtr->SetDead(true);

			if (bouncer_collider->TypeOfContact == ContactType::Bouncer && bouncer_collider->ObjPtr->valid_ == true)
				bouncer_collider->ObjPtr->ContactReaction();

			return;
		}


		// Or the opposite ?
		ball_collider = reinterpret_cast<ContactEvent<Ball, ContactType::Ball>*>(userDataB);
		bouncer_collider = reinterpret_cast<ContactEvent<Bouncer, ContactType::Bouncer>*>(userDataA);

		if (ball_collider->TypeOfContact == ContactType::Ball && bouncer_collider->TypeOfContact == ContactType::Bouncer) {
			std::cout << "B is a ball, A a limit" << " names : " << ball_collider->ObjPtr->_name << ":" << bouncer_collider->ObjPtr->_name << std::endl;

			if (ball_collider->TypeOfContact == ContactType::Ball && ball_collider->ObjPtr->valid_ == true)
				ball_collider->ObjPtr->SetDead(true);

			if (bouncer_collider->TypeOfContact == ContactType::Bouncer && bouncer_collider->ObjPtr->valid_ == true)
				bouncer_collider->ObjPtr->ContactReaction();

			return;
		}

		//// Or two balls toogether ??
		auto ballA_collider = reinterpret_cast<ContactEvent<Ball, ContactType::Ball>*>(userDataA);
		auto ballB_collider = reinterpret_cast<ContactEvent<Ball, ContactType::Ball>*>(userDataB);

		if (ballA_collider->TypeOfContact == ContactType::Ball && ballB_collider->TypeOfContact == ContactType::Ball) {
			std::cout << "Both are balls ! " << ballB_collider->ObjPtr->_name << " : " << ballA_collider->ObjPtr->_name << std::endl;

			if(ballA_collider->TypeOfContact == ContactType::Ball && ballA_collider->ObjPtr->valid_ == true)
				ballA_collider->ObjPtr->SetNewColor(sf::Color::Cyan);

			if(ballB_collider->TypeOfContact == ContactType::Ball && ballB_collider->ObjPtr->valid_ == true)
				ballB_collider->ObjPtr->SetNewColor(sf::Color::Magenta);
		}

	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "End Contact" << std::endl;
}	