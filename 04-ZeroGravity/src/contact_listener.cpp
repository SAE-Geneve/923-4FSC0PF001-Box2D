#include "../include/contact_listener.h"


MyContactListener::MyContactListener()
{

}

void MyContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Contact Begin!";

	//obtain Ball pointer from user data
	auto* sensor_a = reinterpret_cast<MySensor*>(contact->GetFixtureA()->GetUserData().pointer);
	if (sensor_a != nullptr) {
		std::cout << "with a sensor [A contact]";
		// Treat contact in bouncer class
		sensor_a->SetColor(sf::Color::Yellow);
	}
	auto* sensor_b = reinterpret_cast<MySensor*>(contact->GetFixtureB()->GetUserData().pointer);
	if (sensor_b != nullptr) {
		std::cout << "with a sensor [B contact]";
		// Treat contact in bouncer class
		sensor_b->SetColor(sf::Color::Yellow);
	}
	std::cout << std::endl;

}

void MyContactListener::EndContact(b2Contact* contact)
{
	std::cout << "Contact End!";

	//obtain Ball pointer from user data
	auto* sensor_a = reinterpret_cast<MySensor*>(contact->GetFixtureA()->GetUserData().pointer);
	if (sensor_a != NULL) {
		std::cout << "with a bouncer [A contact]";
		// Treat contact in bouncer class
		sensor_a->SetColor(sf::Color::Cyan);
	}
	auto* sensor_b = reinterpret_cast<MySensor*>(contact->GetFixtureB()->GetUserData().pointer);
	if (sensor_b != NULL) {
		std::cout << "with a bouncer [B contact]";
		// Treat contact in bouncer class
		sensor_b->SetColor(sf::Color::Cyan);
	}

	std::cout << std::endl;
}
