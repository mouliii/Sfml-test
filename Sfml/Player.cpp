#include "Player.h"
#include <assert.h>

Player::Player(const sf::Vector2f & pos, b2World* world)
	:
	pos(pos)
{
	std::string path = "Textures\\zelda.png";
	animations[(int)AnimationIndex::Right] = Animation(path, 8, 0.1f, 0, 7 * 130, 120, 130);
	animations[(int)AnimationIndex::Left] = Animation(path, 8, 0.1f, 0, 5 * 130, 120, 130);
	animations[(int)AnimationIndex::IdleLeft] = Animation(path, 1, 10.1f, 0, 1 * 130, 120, 130);
	animations[(int)AnimationIndex::IdleRight] = Animation(path, 1, 10.1f, 0, 3 * 130, 120, 130);
	sprite.setOrigin(130.f / 2, 120.f / 2);
	sprite.scale({ spriteScale,spriteScale});

	// make body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x/ SCALE * spriteScale, pos.y / SCALE * spriteScale);
	body = world->CreateBody(&bodyDef);
	//body->SetGravityScale(0.3f);
	//body->SetBullet(true);
	body->SetFixedRotation(true);
	// fixture
	b2CircleShape circleShape;
	circleShape.m_radius = 60.0f / SCALE * spriteScale;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.5f;
	fixtureDef.friction = 0.7f;
	fixture = body->CreateFixture(&fixtureDef);
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
	if (jumping && canJump)
	{
		//body->SetLinearVelocity({ vel.x,-5.f});
		body->ApplyForce(b2Vec2(0, -5.f), body->GetWorldCenter(), false);
		
		canJump = false;
		jumping = false;
	}
	else
	{
		if (CheckCollision() )
		{
			canJump = true;
		}
	}
	vel.y += 10.f;
	vel = dir * speed;
	body->ApplyForce(b2Vec2(dir.x, 0), body->GetWorldCenter(),true);
}

void Player::Update(float dt)
{
	pos += vel * dt;
	animations[(int)curAnimation].Update(dt);
	animations[(int)curAnimation].Apply(sprite);
	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	
}

void Player::Jump()
{
	jumping = true;
}

bool Player::CheckCollision()
{
	return body->GetContactList();
}
