#include "Animation.h"
#include <assert.h>

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> AssetManager::texturesPtrs;

Animation::Animation(const std::string path, int nFrames, float holdTime, int x, int y, int width, int height)
	:
	nFrames(nFrames),
	holdTime(holdTime)
{
	pTex = AssetManager::Acquire(path);
	for (int i = 0; i < nFrames; i++)
	{
		sf::IntRect frame;
		frame = { x + i * width, y,width, height };
		frames.push_back(frame);
	}
}

void Animation::Apply(sf::Sprite & sprite) const
{
	sprite.setTexture(*pTex);
	sprite.setTextureRect(frames[iFrame]);
}

void Animation::Update(float dt)
{
	time += dt;
	while (time >= holdTime)
	{
		time -= holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++iFrame >= frames.size() )
	{
		iFrame = 0;
	}
}