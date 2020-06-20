#include <SFML/Graphics.hpp>
#include "drawable.h"

Drawable::Drawable(){}
Drawable::~Drawable(){}

Drawable::Drawable(const std::string &filename, int pos_x, int pos_y){
    setPosition(pos_x, pos_y);
    setTexture(filename);
}

void Drawable::setPosition(const float pos_x, const float pos_y){
    sprite_.setPosition(pos_x,pos_y);
}

void Drawable::setRotation(const float angle){
    sprite_.setRotation(angle);
}

void Drawable::setTexture(const std::string &filename){
    texture_.loadFromFile(filename);
    sprite_.setTexture(texture_);
}

void Drawable::drawOn(sf::RenderWindow &window){
    window.draw(sprite_);
}

float Drawable::x() const{ return sprite_.getPosition().x; }
float Drawable::y() const{ return sprite_.getPosition().y; }
