#include "TSceneIntersec_.h"

Vector3f_ TSceneIntersection_::refract_ray(const Vector3f_ &R_i, const Vector3f_ &N, const float eta_t, const float eta_i) {
    float cos_i = - std::max(-1.f, std::min(1.f, R_i * N));

    if (cos_i < 0) { // ? just in case ray is coming from inside
        return this->refract_ray(R_i, -N, eta_i, eta_t);
    }

    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cos_i * cos_i);

    // ? k < 0 -> total reflection, but still reflect it
    return k < 0 ? Vector3f_{1, 0, 0} : R_i * eta + N * (eta * cos_i - std::sqrt(k)); 
}