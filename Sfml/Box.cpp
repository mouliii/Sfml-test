#include "Box.h"

Box::Box()
{
}

void Box::Init(b2World* world, const b2Vec2 & pos, const b2Vec2 & dimensions, float density)
{

	// make body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->CreateBody(&bodyDef);
	// fixture
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);

	// texture
	rect.setPosition(pos.x, pos.y);
	rect.setFillColor(sf::Color::Blue);
	rect.setSize({ dimensions.x,dimensions.y });
}

void Box::Draw(sf::RenderTarget & rt)
{
	rt.draw(rect);
}

void Box::Update()
{
	sf::Vector2f position = { GetBody()->GetPosition().x ,GetBody()->GetPosition().y };
	rect.setPosition(position);
	rect.setRotation(body->GetAngle());
}
