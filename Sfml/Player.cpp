#include "Player.h"
#include <assert.h>

Player::Player(const sf::Vector2f & pos)
	:
	pos(pos)
{
	std::string path = "Textures\\zelda.png";
	animations[(int)AnimationIndex::Right] = Animation(path, 8, 0.1f, 0, 7 * 130, 120, 130);
	animations[(int)AnimationIndex::Left] = Animation(path, 8, 0.1f, 0, 5 * 130, 120, 130);
	animations[(int)AnimationIndex::IdleLeft] = Animation(path, 1, 10.1f, 0, 1 * 130, 120, 130);
	animations[(int)AnimationIndex::IdleRight] = Animation(path, 1, 10.1f, 0, 3 * 130, 120, 130);
	sprite.scale({ 0.5f,0.5f });
}

void Player::Draw(sf::RenderTarget & rt) const
{
	rt.draw(sprite);
}

void Player::SetDir(const sf::Vector2f & dir)
{
	if (dir.x > 0)
	{
		curAnimation = AnimationIndex::Right;
	}
	else if (dir.x < 0)
	{
		curAnimation = AnimationIndex::Left;
	}
	else
	{
		if (vel.x > 0.0f )
		{
			curAnimation = AnimationIndex::IdleRight;
		}
		else if (vel.x < 0.0f)
		{
			curAnimation = AnimationIndex::IdleLeft;
		}
	}
	vel = dir * speed;
}

void Player::Update(float dt)
{
	pos += vel * dt;
	animations[(int)curAnimation].Update(dt);
	animations[(int)curAnimation].Apply(sprite);
	sprite.setPosition(pos);
}
