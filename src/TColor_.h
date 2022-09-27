#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

typedef unsigned char RGB_T;

// ----------------------------------------------------------------

class TColor_ {

public:
	RGB_T     red_;
	RGB_T   green_;
	RGB_T    blue_;

	double   fRed_;
	double fGreen_;
	double  fBlue_;

	TColor_():
		red_(0xFF), green_(0xFF), blue_(0xFF),
		fRed_(1), fGreen_(1), fBlue_(1) {};

	TColor_(RGB_T r, RGB_T g, RGB_T b):
		red_(r), green_(g), blue_(b), fRed_((double) r / 0xFF), fGreen_((double) g / 0xFF), fBlue_((double) b / 0xFF) {};

	void limit_float_values();

	void HEX_to_float();

	sf::Color TtoColor_SFML();

	std::ostream& operator<<(std::ostream& outStream);

	TColor_ operator*(double scalar) const;
	TColor_ operator*(const TColor_& mulColor) const;

	void operator*=(const TColor_& mulColor);
	void operator*=(const double scalar);

	void operator+=(const TColor_& mulColor);
	TColor_ operator+(TColor_ mulColor) const;
};

// ----------------------------------------------------------------