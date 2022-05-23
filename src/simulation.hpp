#pragma once

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

#include "body.hpp"
#include "borders.hpp"
#include "force.hpp"

double randab(const double a, const double b) {
    return static_cast<double> (rand()) / static_cast<double> (RAND_MAX) * (b-a) + a;
}

double sign(const double x) {
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

class Simulation {
    public:

        std::vector<Body*> bodies = std::vector<Body*>();
        Borders *bounds;
        std::vector<Force> *forces;

        Simulation(const int n, Borders *b, std::vector<Force> *forces) {
            assert(n >= 0);
            assert(b);
            bounds = b;
            for(int i=0; i<n; i++) {
                Body *b = new Body(
                    //V2(randab(0, bounds->w), randab(0, bounds->h)),
                    V2(randab(bounds->w*0.4, bounds->w*0.6), randab(bounds->h*0.4, bounds->h*0.6)),
                    V2(0, 0),
                    1,
                    1
                );
                bodies.push_back(b);
            }
            this->forces = forces;
        }

        ~Simulation() {
            delete bounds;
            for (long unsigned int i=0; i<bodies.size(); i++) {
                delete bodies[i];
                bodies[i] = NULL;
            }
        }

        void addBody(Body *b) {
            bodies.push_back(b);
        }

        void update_point(const int i) {
            Body *b = bodies[i];
            b->acc = b->force / b->mass;// * DT; // TODO fix later
            b->speed += b->acc;
            b->position += b->speed;
            
            b->force.x = b->force.y = 0.0f;
            
            bounds->apply(b);
        }

        /*
            Returns true if it has found some collisions.
            False otherwise.
        */
        bool detectAndResolveCollisions() {
            bool foundCollisions = false;
            const unsigned int n = bodies.size();
            for(unsigned int i=0; i<n; i++) {
                Body *first = bodies[i];
                for(unsigned int j=i+1; j<n; j++) {
                    Body *second = bodies[j];

                    if(first->collidesWith(second)) {
                        // we have found a collision
                        foundCollisions = true;

                        // vector pointing first (but centered in origin)
                        V2 diff = first->position.sub(second->position);

                        /*
                            Computing the magnitude of the movement as result of this system.
                            R1 = a + b;
                            R2 = b + c;
                            compenetration = a + b + c

                            we want to find b because it represents the distance to be covered in order
                            to avoid the collision.
                            If b was zero, we would have no collisions.
                            b can be as high as min(R1, R2).

                            The resulting formula is
                            b = R1 + R2 - compenetration
                              = (a+b) + (b+c) - (a+b+c)
                        */
                        const double compenetration = diff.mod();
                        const double b = first->radius + second->radius - compenetration;

                        first->position += (diff * (b/2));
                        second->position -= (diff * (b/2));
                    }
                }
            }
            return foundCollisions;
        }

        void update() {
            //while(detectAndResolveCollisions()) {}
            // TODO: if you do too many iterations, some body will be pushed outside the domain borders
            for(int i=0; i<10; i++) {
                if(!detectAndResolveCollisions()) {
                    break;
                }
            }

            // compute forces
            for(unsigned int i=0; i<forces->size(); i++) {
                //forces->get(i).apply(bodies); // TODO find a way around this uglyness
                forces->at(i).apply(bodies);
            }

            // apply forces
            for(unsigned int i=0; i<bodies.size(); i++) {
                update_point(i);
            }
        }

        void render(sf::RenderWindow *window) {
            for(unsigned int i=0; i<bodies.size(); i++) {
                bodies[i]->circle.setPosition(bodies[i]->position.x, bodies[i]->position.y);
                window->draw(bodies[i]->circle);
            }
        }
};