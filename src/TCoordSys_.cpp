/*

#include "TCoordSys_.h"

void TCoordSys_::draw(sf::RenderWindow* window) {
	if (window == nullptr) {
		throw std::invalid_argument("received invalid sf::RenderWindow");
	}

	Vector_ x_axis(normal, this->xmax_ - this->xmin_, 0);
	Vector_ y_axis(normal, 0, -(this->ymax_ - this->ymin_));

	x_axis.draw(window, this->origin().x() + this->xmin_, get_y_offset(this->origin().y(), window));
	y_axis.draw(window, this->origin().x(), get_y_offset(this->origin().y(), window) - this->ymin_);
}

int TCoordSys_::get_y_offset(int this_y, sf::RenderWindow* window) {
	if (window == nullptr) {
		throw std::invalid_argument("received invalid sf::RenderWindow");
	}

	int window_y = window->getSize().y;
	return this_y < 0 || this_y > window_y ? 0 : window_y - this_y;
}



int get_y_offset(int this_y, sf::RenderWindow* window) {
	if (window == nullptr) {
		throw std::invalid_argument("received invalid sf::RenderWindow");
	}

	int window_y = window->getSize().y;
	return this_y < 0 || this_y > window_y ? 0 : window_y - this_y;
}
*/