#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <cmath>

const float G = 1e-6;
const float FRICTION = 0.99;
const float EPS = 1e-6;

float randab(const float a, const float b) {
    return static_cast<float> (rand()) / static_cast<float> (RAND_MAX) * (b-a) + a;
}

float sign(const float x) {
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

float square(const float x) {
    return x*x;
}

class Simulation {
    public:

        int n;
        float w;
        float h;
        sf::Vertex *points;
        sf::Vector2f *speed;
        sf::Vector2f *acc;
        float *mass;
        sf::Vector2f *force;

        Simulation(const int nPoints, const float width, const float height) : n{nPoints}, w{width}, h{height} {
            points = new sf::Vertex[n];
            speed = new sf::Vector2f[n];
            acc = new sf::Vector2f[n];
            mass = new float[n];
            force = new sf::Vector2f[n];

            for(int i=0; i<n; i++) {
                // random position
                points[i] = sf::Vertex(
                    sf::Vector2f(randab(0, w), randab(0, h)),
                    sf::Color::Red
                );

                // random speed
                //speed[i] = sf::Vector2f(randab(-1, 1), randab(-1, 1));
                speed[i] = sf::Vector2f();

                acc[i] = sf::Vector2f(0, 0);
                mass[i] = 1.0;
                force[i] = sf::Vector2f(0, 0);
            }
        }

        ~Simulation() {
            delete points;
            delete speed;
            delete acc;
            delete mass;
            delete force;
        }

        void update_point(const int i) {
            acc[i] = force[i] / mass[i];
            speed[i] += acc[i];
            points[i].position += speed[i];
            
            force[i] = sf::Vector2f(0, 0); // may be slow to create a new Vector2f each time
            
            points[i].position.x = fmodf(points[i].position.x + w, w);
            points[i].position.y = fmodf(points[i].position.y + h, h);
        }

        void computeForceBetweenBodies(const int i, const int j) {
            // the numerator of the Newton's formula
            const float numerator = G * mass[i] * mass[j];

            const float distX = points[i].position.x - points[j].position.x;
            const float distSqX = fmaxf(square(distX), EPS);
            const float fx = (numerator / distSqX) * FRICTION;
            force[i].x += (fx * sign(distX));
            force[j].x -= (fx * sign(distX));

            const float distY = points[i].position.y - points[j].position.y;
            const float distSqY = fmaxf(square(distY), EPS);
            const float fy = (numerator / distSqY) * FRICTION;
            force[i].y += (fy * sign(distY));
            force[j].y -= (fy * sign(distY));
        }

        void computeForceOnBody(const int i) {
            for(int j=i+1; j<n; j++) {
                computeForceBetweenBodies(i, j);
            }
        }

        void update() {
            // compute forces
            for(int i=0; i<n; i++) {
                computeForceOnBody(i);
            }

            // apply forces
            for(int i=0; i<n; i++) {
                update_point(i);
            }
        }
};

#endif // SIMULATION_HPP