#include "Map.h"
#include <assert.h>

Map::Map(std::string number)
{
	InitMap(number);
}

void Map::InitMap(std::string level)
{
	lvl += std::string("levels//level") + std::string(level) + std::string(".txt");
	std::ifstream myFile;
	myFile.open(lvl);
	if (myFile.good() )  // read level file
	{
		char asd;
		while (myFile.get(asd) )
		{
			// position
			auto tilePos = sf::Vector2f(pos.x, pos.y);
			// push tiles from file to vector
			switch (asd)
			{
			case '#':
			{
				Tile tile(tilePos,sf::Color::Red );
				tiles.push_back(tile);
				pos.x += dimension;
			}
			break;
			case '¤':
			{
				Tile tile(tilePos, sf::Color::Green );
				tiles.push_back(tile);
				pos.x += dimension;
			}
			break;
			case ' ':
				pos.x += dimension;
				break;
			case 'Q':
				pos.y += dimension;
				pos.x = 0;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		assert(myFile.bad() );
	}
}

void Map::DrawMap(sf::RenderTarget& rt)
{
	for (auto& tile : tiles)
	{
		tile.DrawTile(rt);
	}
}

Map::Tile::Tile(sf::Vector2f& pos_in, sf::Color c_in)
	:
	pos(pos_in),
	c(c_in)
{
	rect.setPosition(pos_in);
	rect.setSize(sf::Vector2f(dimension,dimension));
	rect.setOrigin(sf::Vector2f(dimension, dimension) / 2.0f);
}

void Map::Tile::DrawTile(sf::RenderTarget& rt)
{
	rect.setFillColor(c);
	rt.draw(rect);
}

sf::RectangleShape Map::Tile::GetRect()
{
	return rect;
}
