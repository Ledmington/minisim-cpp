#pragma once

#include <vector>

#include "simulation.hpp"
#include "borders.hpp"

class SimulationBuilder {
    private:
        unsigned int n = 0;
        int w = -1;
        int h = -1;
        std::vector<Force> forces = std::vector<Force>();

        typedef enum {
            SOLID,
            CYCLIC
        } BorderType;
        BorderType borderType;

    public:
        SimulationBuilder() {}

        SimulationBuilder nBodies(const unsigned int x) {
            n = x;
            return *this;
        }

        SimulationBuilder width(const int width) {
            w = width;
            return *this;
        }

        SimulationBuilder height(const int height) {
            h = height;
            return *this;
        }

        SimulationBuilder addForce(const Force f) {
            forces.push_back(f);
            return *this;
        }

        SimulationBuilder solidBorders() {
            borderType = SOLID;
            return *this;
        }

        SimulationBuilder cyclicBorders() {
            borderType = CYCLIC;
            return *this;
        }

        Simulation* build() {
            Borders *b;
            switch(borderType) {
                case SOLID:
                {
                    SolidBorders *sb = new SolidBorders(w, h);
                    b = sb;
                    break;
                }
                case CYCLIC:
                {
                    CyclicBorders *cb = new CyclicBorders(w, h);
                    b = cb;
                    break;
                }
                default:
                {
                    b = NULL;
                    break;
                }
            }
            return new Simulation(n, b, &forces);
        }
};