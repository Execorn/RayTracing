#pragma once

#include "SFML/Graphics.hpp"
#include "TVector_.h"
#include "TColor_.h"

class Tvertex_ {

public:
    Tvertex_(int x, int y, RGB_T r, RGB_T g, RGB_T b):
        coordinates({x, y}), color(r, g, b) {}

    Tvertex_():
        coordinates({0, 0}), color(0, 0, 0) {}    

    Vector2i_ coordinates;

    TColor_ color;

    sf::Vertex TtoVtx_SFML() {
        sf::Vertex required({(float) this->coordinates.x_, (float) this->coordinates.y_}, color.TtoColor_SFML());
        return required;
    }
};