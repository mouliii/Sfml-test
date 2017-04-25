#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "AssetManager.h"

class Animation
{
public:
	Animation() = default;
	Animation(const std::string path, int nFrames,float holdTime,int x, int y, int width, int height);
	void Apply(sf::Sprite& sprite) const;
	void Update(float dt);
	void Advance();
private:
	int nFrames;
	float holdTime;
	std::shared_ptr<sf::Texture> pTex;
	std::vector<sf::IntRect> frames;
	int iFrame = 0;
	float time = 0.0f;
};