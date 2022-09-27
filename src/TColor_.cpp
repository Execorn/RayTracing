#include "TColor_.h"

// ----------------------------------------------------------------

void TColor_::limit_float_values() {
	if (fRed_   > 1) fRed_   = 1;
    if (fGreen_ > 1) fGreen_ = 1;
    if (fBlue_  > 1) fBlue_  = 1;

    red_   = RGB_T(fRed_   * 0xFF);
	green_ = RGB_T(fGreen_ * 0xFF);
    blue_  = RGB_T(fBlue_  * 0xFF);
}

// ----------------------------------------------------------------

void TColor_::HEX_to_float() {
	fRed_   = (double) red_ 	/ 0xFF;
	fGreen_ = (double) fGreen_ 	/ 0xFF;
	fBlue_  = (double) fBlue_ 	/ 0xFF;
}

sf::Color TColor_::TtoColor_SFML() {
	sf::Color required(this->red_, this->green_, this->blue_, 0xFF);
	return required;
}

// ----------------------------------------------------------------

std::ostream& TColor_::operator<<(std::ostream& outStream) {
    outStream << "(" << fRed_ << " : " << fGreen_ << " : " << fBlue_ << ")";
    return outStream;
}

// ----------------------------------------------------------------

void TColor_::operator*=(const TColor_& other) {
	fRed_   *= other.fRed_;
	fGreen_ *= other.fGreen_;
	fBlue_  *= other.fBlue_;

	limit_float_values();
}

// ----------------------------------------------------------------

void TColor_::operator*=(const double scalar) {
	fRed_   *= scalar;
	fGreen_ *= scalar;
	fBlue_  *= scalar;

	limit_float_values();
}

// ----------------------------------------------------------------

void TColor_::operator+=(const TColor_& other) {
	fRed_   += other.fRed_;
	fGreen_ += other.fGreen_;
	fBlue_  += other.fBlue_;

	limit_float_values();
}

// ----------------------------------------------------------------

TColor_ TColor_::operator*(double scalar) const {
	TColor_ result = *this;

	result.fRed_   *= scalar;
	result.fGreen_ *= scalar;
	result.fBlue_  *= scalar;

	result.limit_float_values();
	return result;
}

// ----------------------------------------------------------------

TColor_ TColor_::operator*(const TColor_& other) const {
	TColor_ result = *this;
	result *= other;

	return result;
}

// ----------------------------------------------------------------

TColor_ TColor_::operator+(TColor_ other) const {
	TColor_ result = *this;
	result += other;

	result.limit_float_values();
	return result;
}

// ----------------------------------------------------------------