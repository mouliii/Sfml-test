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
				case 'B':
			{
					Box box;
					box.Init(world, { tilePos.x,tilePos.y }, { 20.0f,20.0f }, 0.3f);
					boxes.push_back(box);
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
	for (auto& box : boxes)
	{
		box.Draw(rt);
	}
}

void Map::UpdateBoxes()
{
	for (auto& box : boxes)
	{
		box.Update();
	}
}

Map::Tile::Tile(b2World* world,sf::Vector2f& pos_in, sf::Color c_in)
	:
	pos(pos_in),
	c(c_in)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(pos_in.x / SCALE,pos_in.y / SCALE);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(dimension/2/ SCALE,dimension/2/ SCALE);
	groundBody->CreateFixture(&groundBox, 0.0f);
	// texture ground
	rect.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
	rect.setFillColor(sf::Color::Blue);
	rect.setOrigin(dimension / 2.f , dimension / 2.f);
	rect.setSize({dimension,dimension});
	rect.setFillColor(c);
}

void Map::Tile::DrawTile(sf::RenderTarget& rt)
{
	rt.draw(rect);
}

sf::RectangleShape Map::Tile::GetRect()
{
	return rect;
}
