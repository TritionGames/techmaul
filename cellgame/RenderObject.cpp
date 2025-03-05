#include"RenderObject.h"
#include"SFML/Graphics.hpp"
#include"settings.h"
#include <assert.h>
#include<iostream>

RenderObject::RenderObject(sf::RenderWindow* window, sf::Texture& texture, sf::Vector2f position) {
	setTexture(texture);
	this->sprite = sprite;
	this->window = window;
	this->sprite.setPosition(position);
}

RenderObject::~RenderObject() {
	this->window = nullptr;

}

void RenderObject::render() {
	this->window->draw(this->sprite);
}

void RenderObject::setTexture(sf::Texture& texture) {
	this->sprite.setTexture(texture);
}