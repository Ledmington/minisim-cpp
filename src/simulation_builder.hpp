#ifndef SIM_BUILDER_HPP
#define SIM_BUILDER_HPP

#include "simulation.hpp"
#include "borders.hpp"

class SimulationBuilder {
    private:
        int n;
        int w;
        int h;

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

        SimulationBuilder solidBorders() {
            borderType = SOLID;
            return *this;
        }

        SimulationBuilder cyclicBorders() {
            borderType = CYCLIC;
            return *this;
        }

        Simulation build() {
            switch(borderType) {
                case SOLID:
                {
                    SolidBorders b = SolidBorders(w, h);
                    Borders& bounds = b;
                    return Simulation(n, &bounds);
                }
                case CYCLIC:
                {
                    CyclicBorders b = CyclicBorders(w, h);
                    Borders& bounds = b;
                    return Simulation(n, &bounds);
                }
            }
            return NULL;
        }
};

#endif // SIM_BUILDER_HPP