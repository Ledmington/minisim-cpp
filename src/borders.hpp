#pragma once

#include "body.hpp"

class Borders {
    public:

        double w;
        double h;

        Borders(const double width, const double height) {
            assert(width > 0);
            assert(height > 0);
            this->w = width;
            this->h = height;
        }

        virtual ~Borders() {}

        virtual void apply(Body *b) {}
};

class CyclicBorders : public Borders {
    public:
        CyclicBorders(const double w, const double h) : Borders(w, h) {}
        ~CyclicBorders() {}

        void apply(Body *b) {
            b->position.x = fmodf(b->position.x + w, w);
            b->position.y = fmodf(b->position.y + h, h);
        }
};

class SolidBorders : public Borders {
    public:
        SolidBorders(const double w, const double h) : Borders(w, h) {}
        ~SolidBorders() {}

        void apply(Body *b) override {
            if(b->position.x < 0) {
                b->position.x = 0;
                b->speed.x *= -1;
            } else if(b->position.x > w) {
                b->position.x = w;
                b->speed.x *= -1;
            }

            if(b->position.y < 0) {
                b->position.y = 0;
                b->speed.y *= -1;
            } else if(b->position.y > h) {
                b->position.y = h;
                b->speed.y *= -1;
            }
        }
};