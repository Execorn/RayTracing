#include "TWindow_.h"

// ----------------------------------------------------------------

bool TWindow_::getPollEvent(TEvent_* expectedEvent) {
    sf::Event current_event = {};
    // filling the event structure
    if (window_.pollEvent(current_event) == 0) return false;

    switch (current_event.type) {
        case sf::Event::Closed: {
            (*expectedEvent).event_type = TEvent_::Type::windowClosed;
            break;
        }

        case sf::Event::MouseButtonPressed: {
            (*expectedEvent).event_type = TEvent_::Type::mouseButtonPressed;
            (*expectedEvent).mouse_coordinates.x_ = current_event.mouseButton.x;
            (*expectedEvent).mouse_coordinates.y_ = current_event.mouseButton.y;

            break;
        }

        case sf::Event::MouseButtonReleased: {
            (*expectedEvent).event_type = TEvent_::Type::mouseButtonReleased;
            break;
        }

        default: {
            break;
        }   
    }
    
    return true;
}


void TWindow_::resize(size_t width, size_t height) {
	sf::Vector2u size(width, height);
    window_.setSize(size);
}

// ----------------------------------------------------------------

void TWindow_::clear(TColor_ background_color) {
    window_.clear({background_color.red_, background_color.green_, background_color.blue_, 0xFF});
}

// ----------------------------------------------------------------

void TWindow_::display() {
    window_.display();
}

// ----------------------------------------------------------------

TWindow_::TWindow_(size_t width, size_t height, std::string winname):
        width_(width),
        height_(height),
        window_(sf::VideoMode(width, height), winname) {}

// ----------------------------------------------------------------

void TWindow_::render(const TLine_& line) {
    sf::Vertex coords[] = {
        sf::Vertex(line.a().PtoV2f()),
        sf::Vertex(line.b().PtoV2f())
    };

    this->window_.draw(coords, 2, sf::Lines);
}

void TWindow_::render(Tvertex_* points, size_t vertex_cnt) {
    sf::Vertex* vtx_array = new sf::Vertex[vertex_cnt]; 
    for (size_t cur_vtx = 0; cur_vtx < vertex_cnt; ++cur_vtx) {
        vtx_array[cur_vtx] = points[cur_vtx].TtoVtx_SFML();
    }

    this->window_.draw(vtx_array, vertex_cnt, sf::Points);

    delete[] vtx_array;
}

void TWindow_::render(const Vector2f_& vector) {
    sf::Vertex coords[] = {
        sf::Vertex({0, 0}),
        sf::Vertex({vector.x_, vector.y_}),
    };
    this->window_.draw(coords, 2, sf::Lines);
}

void TWindow_::close() {
    window_.close();
}

TWindow_::~TWindow_() {
    window_.close();
}

// ----------------------------------------------------------------