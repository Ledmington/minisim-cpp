#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

#include "body.hpp"
#include "borders.hpp"

const double G = 1e-5;
const double FRICTION = 0.9;
//const double DT = 1e-8;
//const double EPS = 1e-6; // TODO remove if unused

double randab(const double a, const double b) {
    return static_cast<double> (rand()) / static_cast<double> (RAND_MAX) * (b-a) + a;
}

double sign(const double x) {
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

double square(const double x) {
    return x*x;
}

class Simulation {
    public:

        std::vector<Body> bodies = std::vector<Body>();
        Borders *bounds;

        Simulation(const int n, Borders *b) {
            assert(n >= 0);
            bounds = b;
            for(int i=0; i<n; i++) {
                Body b = Body(
                    V2(randab(0, bounds->w), randab(0, bounds->h)),
                    V2(0, 0),
                    1,
                    10
                );
                bodies.push_back(b);
            }
        }

        // Creates an empty simulation
        Simulation(Borders *bounds) : Simulation(0, bounds) {}

        Simulation addBody(Body b) {
            bodies.push_back(b);
            return *this;
        }

        void update_point(const int i) {
            Body *b = &bodies[i];
            b->acc = b->force / b->mass;// * DT; // TODO fix later
            b->speed += b->acc;
            b->position += b->speed;
            
            b->force = V2(0, 0);
            std::cout << "applying borders" << std::endl;
            bounds->apply(b);
        }

        void computeForceBetweenBodies(const int i, const int j) {
            const double distanceSquared = fmax(square(bodies[i].position.x - bodies[j].position.x), 1e-6);
            const double fx = G * bodies[i].mass * bodies[j].mass / distanceSquared;
            const double fy = 1 / fmax(square(bodies[i].position.y - bodies[j].position.y), 1e-12);
            if(bodies[i].position.x < bodies[j].position.x) {
                bodies[i].force.x += fx;
                bodies[j].force.x -= fx;
            } else {
                bodies[i].force.x -= fx;
                bodies[j].force.x += fx;
            }

            if(bodies[i].position.y < bodies[j].position.y) {
                bodies[i].force.y += fy;
                bodies[j].force.y -= fy;
            } else {
                bodies[i].force.y -= fy;
                bodies[j].force.y += fy;
            }

            //printf("(%d, %d) -> fx: %e, fy: %e\n", i, j, fx, fy);

            /*
            // Newton's formula on x
            const double distX = points[i].position.x - points[j].position.x;
            const double distSqX = fmax(square(distX), 1e-12); // TODO make 1e-12 a constant
            const double fx = (G * mass[i] * mass[j] / distSqX) * FRICTION;
            force[i].x += (fx * sign(distX));
            force[j].x -= (fx * sign(distX));

            // Newton's formula on y
            const double distY = points[i].position.y - points[j].position.y;
            const double distSqY = fmax(square(distY), 1e-12); // TODO make 1e-12 a constant
            const double fy = (G * mass[i] * mass[j] / distSqY) * FRICTION;
            force[i].y += (fy * sign(distY));
            force[j].y -= (fy * sign(distY));
            */
        }

        void computeForceOnBody(const int i) {
            const unsigned int n = bodies.size();
            for(unsigned int j=i+1; j<n; j++) {
                computeForceBetweenBodies(i, j);
            }
        }

        /*
            Returns true if it has found some collisions.
            False otherwise.
        */
        bool detectAndResolveCollisions() {
            bool foundCollisions = false;
            const unsigned int n = bodies.size();
            for(unsigned int i=0; i<n; i++) {
                Body *first = &bodies[i];
                for(unsigned int j=i+1; j<n; j++) {
                    Body *second = &bodies[j];

                    if(first->collidesWith(second)) {
                        // we have found a collision
                        foundCollisions = true;

                        // vector pointing first (but centered in origin)
                        V2 diff = first->position.sub(second->position);
                        V2 spos = diff.norm();

                        /*
                            Computing the magnitude of the movementas the result of this system.
                            R1 = a + b;
                            R2 = b + c;
                            compenetration = a + b + c

                            we want to find b because it represents the distance to be covered in order
                            to avoid the collision.
                            If b was zero, we would have no collisions.
                            b can be as high as min(R1, R2).

                            The resulting formula is
                            b = R2 - compenetration - R1
                              = (b+c) - (a+b+c) - (a+b)
                        */
                       const double compenetration = diff.mod();
                       const double b = second->radius - compenetration - first->radius;

                       first->position += spos * (b/2);
                       second->position -= spos * (b/2);

                        /*
                        const double distsq = diff.dot(diff);
                        const double Rsum = first->radius + second->radius;
                        if (distsq < Rsum*Rsum - EPS) {
                            const double dist = sqrt(distsq);
                            const Vec3 force = vmul(vmul(diff, 1/dist), (Rsum - dist)*KAPPA);
                            s->F = vsub(s->F, force);
                            other->F = vadd(other->F, force);
                        }*/
                    }
                }
            }
            return foundCollisions;
        }

        void update() {
            // TODO may be simplified to do just k iterations of "detect-and-resolve"
            //while(detectAndResolveCollisions()) {}
            for(int i=0; i<1; i++) {
                std::cout << "collision iteration " << i << std::endl;
                detectAndResolveCollisions();
            }

            std::cout << "computeForces" << std::endl;
            // compute forces
            for(unsigned int i=0; i<bodies.size(); i++) {
                computeForceOnBody(i);
            }

            std::cout << "applyForces" << std::endl;
            // apply forces
            for(unsigned int i=0; i<bodies.size(); i++) {
                update_point(i);
            }
        }

        void render(sf::RenderWindow *window) {
            for(unsigned int i=0; i<bodies.size(); i++) {
                window->draw(bodies[i].circle);
            }
        }
};

#endif // SIMULATION_HPP