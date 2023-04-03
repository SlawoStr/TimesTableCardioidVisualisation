#include <SFML/Graphics.hpp>

class CircleConnector
{
public:
	CircleConnector(sf::Vector2f startingPosition,int circleNumber,float radius);
	void draw(sf::RenderTarget& target);
	void setPosition(sf::Vector2f position);
private:
	std::vector<sf::CircleShape> circleVec;
	float factor{ 0.0f };
	const int circleNumber;
	float smallRadius = 5.f;
	float angle = 0.0f;
};

