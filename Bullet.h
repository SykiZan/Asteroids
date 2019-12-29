#pragma once

#include <SFML\Graphics.hpp>
class Bullet
{

public:

    sf::CircleShape shape;
    sf::Vector2f projectile_velocity;

    Bullet(float radius = 5)
        :projectile_velocity(0.f, 0.f)
    {
        this->shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
    }


};

