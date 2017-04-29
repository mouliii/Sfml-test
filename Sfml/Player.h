#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Animation.h"


class Player
{
public:
	Player(const sf::Vector2f& pos, b2World* world);
	void Draw(sf::RenderTarget& rt)const;
	void SetDir(const sf::Vector2f& dir);
	void Update(float dt);
public:
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }
	sf::Sprite GetSprite() { return sprite; }
private:
	enum class AnimationIndex
	{
		Right,
		Left,
		IdleRight,
		IdleLeft,
		Count
	};
private: // VARIABLES
	static constexpr float speed = 135.0f;
	const float height = 130.0f;
	const float width = 120.0f;
private: // ANIMATION
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Texture texture;
	sf::Sprite sprite;
	Animation animations[(int)AnimationIndex::Count];
	AnimationIndex curAnimation = AnimationIndex::IdleRight;
	bool runRight = false;
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
private:
	const float SCALE = 100.0f;
};