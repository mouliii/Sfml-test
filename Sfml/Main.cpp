#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Player.h"
#include "Map.h"

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// time
	auto tp = std::chrono::steady_clock::now();
	// some bs

	// Load Player
	Player player({ 100.0f,100.0f });
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

		// Draw
		player.Draw(window);
		map.DrawMap(window);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
