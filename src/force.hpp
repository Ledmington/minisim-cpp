#pragma once

#include <vector>
#include <assert.h>

#include "body.hpp"

static constexpr double NEWTON_GRAVITY = 6.6743e-11;

double square(const double x) {
    return x*x;
}

class Force {
    public:

        double constant;

        Force(const double force_constant) {
            constant = force_constant;
        }

        virtual ~Force() {}

        virtual void apply(std::vector<Body*> &bodies) {}
};

class Friction : public Force {
    public:
        Friction(const double friction_constant) : Force(friction_constant) {
            assert(friction_constant > 0 && friction_constant <= 1);
        }

        void apply(std::vector<Body*> &bodies) {
            for(unsigned int i=0; i<bodies.size(); i++) {
                bodies[i]->force *= constant;
            }
        }
};

class Gravity : public Force {
    public:
        Gravity(const double gravitational_constant) : Force(gravitational_constant) {
            assert(gravitational_constant > 0 && gravitational_constant <= 1);
        }

        void apply(std::vector<Body*> &bodies) {
            for(unsigned int i=0; i<bodies.size(); i++) {
                for(unsigned int j=i+1; j<bodies.size(); j++) {
                    computeForceBetweenBodies(bodies[i], bodies[j]);
                }
            }
        }

        void computeForceBetweenBodies(Body *first, Body *second) {
            // vector pointing first (but centered in origin)
            V2 diff = first->position.sub(second->position);
            const double distance = first->dist(second);
            const double force = constant * first->mass * second->mass / square(distance);
            first->force -= (diff * force);
            second->force += (diff * force);
        }
};