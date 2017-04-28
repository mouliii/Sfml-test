#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <chrono>
#include "Player.h"
#include "Map.h"
#include "Box.h"

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.setFramerateLimit(60);
	// Box2d World
	b2Vec2 gravity(0.0f, 10.0f);
	std::unique_ptr<b2World> world;
	world = std::make_unique<b2World>(gravity);
	// time
	auto tp = std::chrono::steady_clock::now();
	// some bs
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(50.0f, 400.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(60.0f, 2.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	// texture ground
	sf::RectangleShape rect;
	rect.setPosition(50.0f, 400.0f);
	rect.setFillColor(sf::Color::Blue);
	rect.setSize({ 60.0f, 2.0f });
	// Load Player
	Player player({ 100.0f,100.0f }, world.get());
	//view
	sf::View view({player.GetBody()->GetPosition().x, player.GetBody()->GetPosition().y}, sf::Vector2f(640, 480));
	window.setView(view);
	//box
	Box box;
	box.Init(world.get(), { 100.0f,100.0f }, { 1.0f,1.0f }, 3.0f);
	// Load map
	Map map("1");

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// get dt
		float dt;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}

		// Input
		sf::Vector2f dir = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dir.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x += 1.0f;
		}
		player.SetDir(dir);
		// Update
		player.Update(dt);
		box.Update();
		world->Step(dt, 6, 2);
		view.setCenter(player.GetBody()->GetPosition().x, player.GetBody()->GetPosition().y);
		window.setView(view);
		// Draw
		player.Draw(window);
		//map.DrawMap(window);
		window.draw(rect);
		box.Draw(window);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}