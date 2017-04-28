#pragma once
#include <Box2D\Box2D.h>
#include "AssetManager.h"

class Box
{
public:
	Box();
	void Init(b2World* world,const b2Vec2& pos, const b2Vec2& dimensions, float density);
	void Draw(sf::RenderTarget& rt);
	void Update();
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }
	sf::RectangleShape GetRect() { return rect; }
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	std::shared_ptr<sf::Texture> pTex;
	sf::RectangleShape rect;
};