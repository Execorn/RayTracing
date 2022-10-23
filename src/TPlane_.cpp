#include "TPlane_.h"

TPlane_::TPlane_(Vector3f_& origin, Vector3f_& normal_vector, TMaterial_ material) {
    this->material_ = material;

    this->a_ = normal_vector.x_;
    this->b_ = normal_vector.y_;
    this->c_ = normal_vector.z_;

    this->d_ = -normal_vector.x_ * origin[0] - normal_vector.y_ * origin[1] - normal_vector.z_ * origin[2];
}

TPlane_::TPlane_(Vector3f_& origin, Vector3f_& vector_1, Vector3f_& vector_2, TMaterial_ material) {
    this->material_ = material;

    this->a_ = vector_1[1] * vector_2[2] - vector_1[2] * vector_2[1];
    this->b_ = vector_1[2] * vector_2[0] - vector_1[0] * vector_2[2];
    this->c_ = vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0];

    this->d_ =  - origin[0] * vector_1[1] * vector_2[2] - origin[2] * vector_1[0] * vector_2[1] +
                - origin[1] * vector_1[2] * vector_2[0] + origin[2] * vector_1[1] * vector_2[0] +
                  origin[0] * vector_1[2] * vector_2[1] + origin[1] * vector_1[0] * vector_2[2];
}

float TPlane_::intersection(const Vector3f_ &origin, const Vector3f_ &direction, TSceneIntersection_* its) const {
    Vector3f_ n(this->a_, this->b_, this->c_);

    float denom = n * direction;
    
    if (abs(denom) <= 1e-4f) {
        its->isHit = false;
        return 0.f;
    }
    
    float t = -(n * origin + this->d_) / (n * direction);

    if (t <= 1e-4) {
        its->isHit = false;
        return 0.f;
    } 

    Vector3f_ final_vector = direction * t;

    its->isHit = true;

    return final_vector.len();
}