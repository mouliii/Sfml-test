#include "Map.h"
#include <assert.h>

Map::Map(std::string number,b2World* world)
{
	InitMap(number,world);
}

void Map::InitMap(std::string level, b2World* world)
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
				Tile tile(world,tilePos,sf::Color::Red );
				tiles.push_back(tile);
				pos.x += dimension;
			}
			break;
			case '¤':
			{
				Tile tile(world,tilePos, sf::Color::Green );
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

Map::Tile::Tile(b2World* world,sf::Vector2f& pos_in, sf::Color c_in)
	:
	pos(pos_in),
	c(c_in)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(pos_in.x,pos_in.y);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(dimension/2,dimension/2);
	groundBody->CreateFixture(&groundBox, 0.0f);
	// texture ground
	rect.setPosition(pos_in.x,pos_in.y);
	rect.setFillColor(sf::Color::Blue);
	rect.setSize({dimension,dimension});
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
