#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "SFML/Graphics.hpp"

class RenderObject {
public:
	RenderObject(sf::RenderWindow* window, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0, 0));
	~RenderObject();

	sf::Sprite sprite;
	sf::RenderWindow* window;

	void setTexture(sf::Texture& texture);
	void render();
};
#endif