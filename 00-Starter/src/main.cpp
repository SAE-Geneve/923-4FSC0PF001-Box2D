#include <iostream>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

int main()
{
    std::cout << "Hello Box 2D World" << std::endl;

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // The floor -------------------------------------------------------------
    b2BodyDef ground_body_def;
    ground_body_def.position.Set(0.0f, -10.0f);
    b2Body* ground_body = world.CreateBody(&ground_body_def);

	b2PolygonShape ground_box;
    ground_box.SetAsBox(50.0f, 10.0f);
    ground_body->CreateFixture(&ground_box, 0.0f);

    // The object --------------------------------------------------------------
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&body_def);

    b2PolygonShape dynamic_box;
    dynamic_box.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_box;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;

    body->CreateFixture(&fixture_def);

    for (int32 i = 0; i < 3000; ++i)
    {
        constexpr float time_step = 0.0001f;
        constexpr int32 velocity_iterations = 6;
        constexpr int32 position_iterations = 2;

    	world.Step(time_step, velocity_iterations, position_iterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        std::cout << "Object position : " << position.x << " : " << position.y << " : " << angle << std::endl;
    }

}


