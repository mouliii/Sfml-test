#include "Box.h"

Box::Box()
{
}

void Box::Init(b2World* world, const b2Vec2 & pos, const b2Vec2 & dimensions, float density)
{

	// make body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x/ SCALE, pos.y/ SCALE);
	body = world->CreateBody(&bodyDef);
	// fixture
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f / SCALE, dimensions.y / 2.0f / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);

	// texture
	rect.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	//rect.setFillColor(sf::Color::Blue);
	rect.setSize({ dimensions.x,dimensions.y });
	rect.setOrigin(dimensions.x / 2, dimensions.y / 2);
	texture.loadFromFile("Textures\\tileTextures.png");
	rect.setTextureRect(sf::IntRect(4*32, 0, 32, 32));
}

void Box::Draw(sf::RenderTarget & rt)
{
	rt.draw(rect);
}

void Box::Update()
{
	rect.setTexture(&texture);
	sf::Vector2f position = { GetBody()->GetPosition().x * SCALE ,GetBody()->GetPosition().y * SCALE };
	rect.setPosition(position);
	rect.setRotation(body->GetAngle() * (180.0f / 3.14f));
}