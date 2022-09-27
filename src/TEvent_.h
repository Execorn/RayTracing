#pragma once

#include "SFML/Graphics.hpp"
#include "TVector_.h"

// ----------------------------------------------------------------

class TEvent_ {

public:
    Vector2f_ mouse_coordinates;

    enum class Type {
        defaultEvent,
        mouseButtonPressed,
        mouseButtonReleased,
        windowClosed,
    };

    Type event_type = Type::defaultEvent;

private:
    sf::Event myevent_ = {};
};

// ----------------------------------------------------------------