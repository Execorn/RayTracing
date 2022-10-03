#include "TSceneIntersec_.h"

Vector3f_ TSceneIntersection_::refract_ray(const Vector3f_ &R_i, const Vector3f_ &N, const float coeff_t, const float coeff_i) {
    float cos_i = -std::max(-1.f, std::min(1.f, R_i * N));

    if (cos_i < 0) { // ? just in case ray is coming from inside
        return this->refract_ray(R_i, -N, coeff_i, coeff_t);
    }

    float final_coeff = coeff_i / coeff_t;
    float k = 1 - final_coeff * final_coeff * (1 - cos_i * cos_i); // ? coefficient of refraction

    // ? k < 0 -> total reflection, but still reflect it
    return k < 0 ?  
            Vector3f_{1, 0, 0} : 
            R_i * final_coeff + N * (final_coeff * cos_i - std::sqrt(k)); 
}