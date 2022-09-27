/*

#pragma once

#include "TLine_.h"
#include "TVector_.h"

class TCoordSys_ {
	TPoint_ origin_;

	double xmin_, xmax_, ymin_, ymax_;
	double scale_;

	public:
	TCoordSys_(TPoint_ origin, double xmin, double xmax, double ymin, double ymax, double scale):
	origin_(origin), xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax), scale_(scale) {
		if (xmin > 0 || xmax < 0 || ymin > 0 || ymax < 0 || scale < 0) {
			throw std::invalid_argument("received invalid parameter");
		}
	}

	void draw(sf::RenderWindow* window);
	int get_y_offset(int this_y, sf::RenderWindow* window);

	double minX() {
		return this->xmin_;
	}

	double maxX() {
		return this->xmax_;
	}

	double minY() {
		return this->ymin_;
	}

	double maxY() {
		return this->ymax_;
	}

	double scale() {
		return this->scale_;
	}

	TPoint_ origin() {
		return this->origin_;
	}
};

*/