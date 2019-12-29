#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Asteroid
{
public:
   // sf::RectangleShape asteroid_shape;
    sf::Sprite asteroid_shape;

    sf::Vector2f asteroid_velocity;

    sf::Vector2f asteroid_size;

    sf::Vector2f asteroid_pos;

    Asteroid()
       : asteroid_size(0.5f, 0.5f) 
    {
        
       // asteroid_shape.setFillColor(sf::Color::Green);
        this->asteroid_shape.setScale(sf::Vector2f(asteroid_size));
        asteroid_shape.setOrigin(20.f, 20.f);
        

    }
};
