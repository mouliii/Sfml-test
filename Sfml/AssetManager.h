#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

class AssetManager
{
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name)
	{
		const auto i = texturesPtrs.find(name);

		if (i != texturesPtrs.end() )
		{
			return i->second;
		}
		else
		{
			auto pTex = std::make_shared<sf::Texture>();
			pTex->loadFromFile(name);
			texturesPtrs.insert({ name,pTex });
			return pTex;
		}
	}
	static void clearAssets()
	{
		for (auto i = texturesPtrs.begin() ; i != texturesPtrs.end(); )
		{
			if (i->second.unique() )
			{
				i = texturesPtrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesPtrs;
};