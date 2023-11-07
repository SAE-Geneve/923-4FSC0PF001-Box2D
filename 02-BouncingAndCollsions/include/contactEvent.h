#pragma once
#include <iostream>
#include <box2d/b2_settings.h>

class Bouncer;
class Ball;

// Event Type -------------------------------------------
enum class ContactType
{
	Ball, Bouncer, None
};

template<typename T, ContactType U>
class ContactEvent
{
public:

	ContactType TypeOfContact = ContactType::None;
	T* ObjPtr = nullptr;

	ContactEvent() : TypeOfContact(ContactType::None)
	{

	};

	ContactEvent(T* objPtr) :
		TypeOfContact(U)
	{
		ObjPtr = objPtr;
	};

	//ContactEvent(Ball& ball) :
	//	TypeOfContact(ContactType::Ball),
	//	Ball(&ball)
	//{

	//};
	//Ball* Ball = nullptr;

	//ContactEvent(Bouncer& bouncer) :
	//TypeOfContact(ContactType::Bouncer),
	//Bouncer(&bouncer)
	//{
	//	
	//};
	//Bouncer* Bouncer = nullptr;


};
