#pragma once

#include "TVector_.h"
#include "TSceneIntersec_.h"
#include "TScene_.h"

class TRay_ {

private:
    const Vector3f_    origin_;
    const Vector3f_ direction_;

public:
    TRay_(Vector3f_ origin, Vector3f_ direction) : origin_(origin), direction_(direction) {}

    TSceneIntersection_ intersect(TScene_& scene);

    Vector3f_ cast_ray(TScene_& scene, const int depth = 0);
}; 