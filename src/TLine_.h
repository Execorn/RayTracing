#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include "TColor_.h"

// ----------------------------------------------------------------

class TPoint_ {
	double x_, y_;

	public:
	TPoint_(double x, double y):
	x_(x), y_(y) {};

	double x() {
		return x_;
	}

	double y() {
		return y_;
	}

	sf::Vector2f PtoV2f() const {
		return sf::Vector2f(x_, y_);
	}
};

// ----------------------------------------------------------------

class TLine_ {
	TPoint_ a_, b_;

	public:
	TLine_(TPoint_ a, TPoint_ b, int t = 0):
	a_(a), b_(b) {};

	void set_first(TPoint_ new_a) {
		this->a_ = new_a;
	}

	void set_second(TPoint_ new_b) {
		this->b_ = new_b;
	}

	TPoint_ a() const { return this->a_; }	
	TPoint_ b() const { return this->b_; }

};

// ----------------------------------------------------------------