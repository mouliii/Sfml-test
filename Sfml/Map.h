#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class Map
{
	class Tile;
public:
	Map(std::string number);
	void InitMap(std::string level);
	void DrawMap(sf::RenderTarget& rt);
private:
	std::vector<Tile> tiles;
	sf::Vector2f pos = { 0,12 };
	std::string lvl;
protected:
	static constexpr float dimension = 32.0f;
private:
	class Tile
	{
	public:
		Tile(sf::Vector2f& pos_in, sf::Color c_in);
		void DrawTile(sf::RenderTarget& rt);
		sf::RectangleShape GetRect();
	private:
		sf::Vector2f pos;
		sf::RectangleShape rect;
		sf::Color c;
		b2BodyDef tileBody;
		b2PolygonShape tileBox;
	};
};