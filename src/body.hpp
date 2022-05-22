#pragma once

#include <cmath>
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
            circle.setRadius(radius);
            this->mass = mass;
            this->radius = radius;
            this->position = pos;
            this->speed = speed;
            this->acc = V2(0, 0);
            this->force = V2(0, 0);
        }

        Body() : Body(V2(0,0), V2(0,0), 1.0, 1.0) {}

        ~Body() {}

        double dist(Body *other) {
            return position.dist(other->position);
        }

        bool collidesWith(Body *other) {
            const double Rsum = radius + other->radius;
            if(fabs(position.x - other->position.x) > Rsum) return false;
            if(fabs(position.y - other->position.y) > Rsum) return false;
            return position.distsq(other->position) < Rsum*Rsum; // faster way (maybe)
            //return dist(other) < Rsum; <-- correct way
        }
};