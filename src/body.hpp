#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>

#include "v2.hpp"

class Body {
    public:
        sf::CircleShape circle;
        double mass;
        double radius;
        V2 position;
        V2 speed;
        V2 acc;
        V2 force;

        Body(V2 pos, V2 speed, double mass, double radius) {
            assert(mass > 0);
            assert(radius > 0);
            circle = sf::CircleShape(radius);
            circle.setFillColor(sf::Color::Red);
        }

        Body() : Body(V2(0,0), V2(0,0), 1, 1) {}

        double dist(Body *other) {
            return position.dist(other->position);
        }
};

#endif // BODY_HPP