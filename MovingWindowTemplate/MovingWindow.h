#pragma once
#include <SFML/Graphics.hpp>
#include "CircleConnector.h"

class MovingWindow
{
public:
	MovingWindow(sf::Vector2u windowSize,sf::String title,sf::Uint32 style = sf::Style::Default,unsigned int framerate = 144);
	void run();
private:
	void pollEvent();
	void update();
	void draw();
	std::pair<sf::Vector2f, sf::Vector2f> getViewBox();
private:
	sf::RenderWindow window;
	float zoomLevel{ 1.0f };
	// Panning
	sf::Vector2i panningAnchor{};
	bool panning{false};
	// Connector settings
	std::vector<CircleConnector> connectors;
	float bigRadius = 2000.f;
	const float smallRadius = 300.0f;
	float angle = 0.0f;
	const int circleNumber = 16;
	const int numberOfConnection = 50;
	float rotationSpeed = 0.01f;
};