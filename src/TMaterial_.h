#pragma once

#include "TVector_.h"

// ----------------------------------------------------------------
// ! https://en.wikipedia.org/wiki/Albedo (measure of diffuse reflection)

class TMaterial_ {

public:
    float 	 refractive_index_ = 1;
    float 			albedo_[4] = {2, 0, 0, 0};
    Vector3f_ 	diffuse_color_ = {0, 0, 0};
    float 	specular_exponent_ = 0;
};

// ----------------------------------------------------------------