#include "MovingWindow.h"
#define PI 3.14159265


MovingWindow::MovingWindow(sf::Vector2u windowSize, sf::String title, sf::Uint32 style, unsigned int framerate ) : window(sf::VideoMode(windowSize.x,windowSize.y), title,style)
{
	// Max Framerate
	window.setFramerateLimit(framerate);
	// Set view to start in the point (0,0)
	sf::View view = window.getView();
	view.move(-static_cast<float>(windowSize.x) / 2, -static_cast<float>(windowSize.x) / 2);
	window.setView(view);

	sf::Vector2f position;
	for (int i = 0; i < circleNumber; ++i)
	{
		position.x = static_cast<float>((bigRadius * std::sin(angle * PI / 180))) + bigRadius - smallRadius;
		position.y = static_cast<float>((bigRadius * std::cos(angle * PI / 180))) + bigRadius - smallRadius;
		connectors.emplace_back(position, numberOfConnection * (i+1),smallRadius);
		angle += static_cast<float>(360) / circleNumber;
	}

}

void MovingWindow::run()
{
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		draw();
		window.display();
		update();
		pollEvent();
	}
}

void MovingWindow::pollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
		{
			sf::View view = window.getView();
			view.setSize(static_cast<float>(e.size.width), static_cast<float>(e.size.height));
			view.zoom(zoomLevel);
			window.setView(view);
			break;
		}
		case sf::Event::MouseMoved:
			if (panning)
			{
				sf::View view = window.getView();
				sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window) - this->panningAnchor);
				view.move(-1.0f * pos * zoomLevel);
				window.setView(view);
				panningAnchor = sf::Mouse::getPosition(window);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Middle)
			{
				panning = true;
				panningAnchor = sf::Mouse::getPosition(window);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button == sf::Mouse::Middle)
			{
				panning = false;
			}
			break;
		case sf::Event::MouseWheelMoved:
		{
			sf::View view = window.getView();
			if (e.mouseWheel.delta < 0)
			{
				view.zoom(2.0f);
				zoomLevel *= 2;
			}
			else
			{
				view.zoom(0.5f);
				zoomLevel *= 0.5;
			}
			window.setView(view);
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (e.key.code == sf::Keyboard::Right)
			{
				bigRadius += 10.0f;
			}
			else if (e.key.code == sf::Keyboard::Left)
			{
				bigRadius -= 10.0f;
			}
			if (e.key.code == sf::Keyboard::Up)
			{
				rotationSpeed += 0.01f;
			}
			else if (e.key.code == sf::Keyboard::Down)
			{
				rotationSpeed -= 0.01f;
			}
			break;
		}
		}
	}
}

void MovingWindow::update()
{
	sf::Vector2f position;
	angle += rotationSpeed;
	for (int i = 0; i < circleNumber; ++i)
	{
		position.x = static_cast<float>((bigRadius * std::sin(angle * PI / 180))) + bigRadius - smallRadius;
		position.y = static_cast<float>((bigRadius * std::cos(angle * PI / 180))) + bigRadius - smallRadius;
		angle += static_cast<float>(360) / circleNumber;
		connectors[i].setPosition(position);
	}
	angle = angle > 360.0f ? angle - 360.f : angle;
}

void MovingWindow::draw()
{
	for (auto& connector : connectors)
	{
		connector.draw(window);
	}
}

std::pair<sf::Vector2f, sf::Vector2f> MovingWindow::getViewBox()
{
	sf::View view = window.getView();
	sf::Vector2f winStart = sf::Vector2f{ view.getCenter().x - view.getSize().x / 2,view.getCenter().y - view.getSize().y / 2 };
	sf::Vector2f winEnd = sf::Vector2f{ view.getCenter().x + view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 };

	return { winStart,winEnd };
}
