#include "CircleConnector.h"
#define PI 3.14159265


CircleConnector::CircleConnector(sf::Vector2f startingPosition,int circleNumber,float bigRadius) : circleNumber(circleNumber)
{
	// Add main Circle
	sf::CircleShape shape;
	shape.setRadius(bigRadius);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color::White);
	shape.setPosition(startingPosition);

	circleVec.push_back(shape);

	// Add Small Circles
	shape.setRadius(smallRadius);
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(0.f);
	sf::Vector2f circlePos;
	for (int i = 0; i < circleNumber; ++i)
	{
		circlePos.x = static_cast<float>((bigRadius * std::sin(angle * PI / 180))) + startingPosition.x + bigRadius - smallRadius;
		circlePos.y = static_cast<float>((bigRadius * std::cos(angle * PI / 180))) + startingPosition.y + bigRadius - smallRadius;
		shape.setPosition(circlePos);
		// Distance between small circles should be identyical
		angle += static_cast<float>(360) / circleNumber;
		circleVec.push_back(shape);
	}
}

void CircleConnector::draw(sf::RenderTarget& target)
{
	// Draw circles
	for (int i = 0; i < circleVec.size(); ++i)
	{
		target.draw(circleVec[i]);
	}

	//Draw connections
	sf::VertexArray lines(sf::Lines);

	sf::Vertex line[2];
	for (int i = 1; i < circleVec.size(); ++i)
	{
		int n = static_cast<int>((i - 1) * factor);
		n %= circleNumber;

		line[0].position.x = circleVec[i].getPosition().x + circleVec[i].getRadius();
		line[0].position.y = circleVec[i].getPosition().y + circleVec[i].getRadius();

		line[1].position.x = circleVec[n + 1].getPosition().x + circleVec[n + 1].getRadius();
		line[1].position.y = circleVec[n + 1].getPosition().y + circleVec[n + 1].getRadius();
		lines.append(line[0]);
		lines.append(line[1]);
	}
	factor += 0.01f;
	target.draw(lines);
}

void CircleConnector::setPosition(sf::Vector2f position)
{
	circleVec[0].setPosition(position);

	sf::Vector2f circlePos;
	
	for (int i = 1; i < circleVec.size(); ++i)
	{
		circlePos.x = static_cast<float>((circleVec[0].getRadius() * std::sin(angle * PI / 180))) + circleVec[0].getPosition().x + circleVec[0].getRadius() - smallRadius;
		circlePos.y = static_cast<float>((circleVec[0].getRadius() * std::cos(angle * PI / 180))) + circleVec[0].getPosition().y + circleVec[0].getRadius() - smallRadius;
		angle += static_cast<float>(360) / circleNumber;

		circleVec[i].setPosition(circlePos);
	}
	angle = angle > 360.0f ? angle - 360.f : angle;
}
