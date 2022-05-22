#pragma once

#include "simulation.hpp"
#include "borders.hpp"

class SimulationBuilder {
    private:
        int n = 0;
        int w;
        int h;
        double g;
        double f;

        typedef enum {
            SOLID,
            CYCLIC
        } BorderType;
        BorderType borderType;

    public:
        SimulationBuilder() {}

        SimulationBuilder nBodies(const int x) {
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

        SimulationBuilder gravity(const double gravity) {
            g = gravity;
            return *this;
        }

        SimulationBuilder friction(const double friction) {
            f = friction;
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
            return new Simulation(n, b, g, f);
        }
};