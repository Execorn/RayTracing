#pragma once

#include "TVector_.h"
#include "TMaterial_.h"

class TSceneIntersection_ {

public:
    bool            isHit;
    Vector3f_       point;

    Vector3f_ unit_vector;
    TMaterial_   material;
    
    TSceneIntersection_(bool hit, Vector3f_ pt, Vector3f_ unv, TMaterial_ mat):
        isHit(hit), point(pt), unit_vector(unv), material(mat) {}    

    TSceneIntersection_(bool hit, Vector3f_ pt):
        isHit(hit), point(pt), unit_vector({0, 0, 0}), material({0, {0, 0, 0, 0}, {0, 0, 0}, 0}) {}    

    Vector3f_ refract_ray(const Vector3f_ &R_i, const Vector3f_ &N, const float eta_t, const float eta_i = 1.f);

    Vector3f_ reflect_ray(const Vector3f_ &R_i, const Vector3f_ &N) {
        return R_i - N * 2.f * (R_i * N);
    }
};