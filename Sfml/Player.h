#include <SFML/Graphics.hpp>
#include "Animation.h"


class Player
{
public:
	Player(const sf::Vector2f& pos);
	void Draw(sf::RenderTarget& rt)const;
	void SetDir(const sf::Vector2f& dir);
	void Update(float dt);
private:
	enum class AnimationIndex
	{
		Right,
		Left,
		IdleRight,
		IdleLeft,
		Count
	};
private: // VARIABLES
	static constexpr float speed = 135.0f;
private: // ANIMATION
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Texture texture;
	sf::Sprite sprite;
	Animation animations[(int)AnimationIndex::Count];
	AnimationIndex curAnimation = AnimationIndex::IdleRight;
	bool runRight = false;
};