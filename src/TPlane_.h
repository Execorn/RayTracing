#pragma once

#include "TVector_.h"
#include "TSceneIntersec_.h"
#include "TMaterial_.h"

static const TMaterial_ DEFAULT_MATERIAL = {1.0, {2, 0, 0, 0}, {0.0, 0.0, 0.0}, 0.};

class TPlane_ {

public:
    
    double a_, b_, c_, d_;
    bool isInfinite_;
    TMaterial_ material_;
    
    TPlane_():
        a_(0), b_(0), c_(0), d_(0), isInfinite_(true), material_(DEFAULT_MATERIAL) {};

    TPlane_(double a, double b, double c, double d, bool isInfinite, TMaterial_ material = DEFAULT_MATERIAL):
        a_(a), b_(b), c_(c), d_(d), isInfinite_(isInfinite), material_(DEFAULT_MATERIAL) {};        

    TPlane_(Vector3f_& origin, Vector3f_& normal_vector, TMaterial_ material = DEFAULT_MATERIAL);

    TPlane_(Vector3f_& origin, Vector3f_& vector_1, Vector3f_& vector_2, TMaterial_ material = DEFAULT_MATERIAL);

    float intersection(const Vector3f_ &origin, const Vector3f_ &direction, TSceneIntersection_* its) const;

    double a() const { return this->a_; }

    double b() const { return this->b_; }
    
    double c() const { return this->c_; }
    
    double d() const { return this->d_; }
};