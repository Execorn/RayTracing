#include "TSphere_.h"

// ----------------------------------------------------------------

// ! http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/

float TSphere_::intersection(const Vector3f_ &origin, const Vector3f_ &direction, TSceneIntersection_* its) const {
	Vector3f_ path_vector = this->center_ - origin; // vector from origin to center

	float to_sphere = path_vector * direction;
	float center_distance  = path_vector * path_vector - to_sphere * to_sphere;

	if (center_distance > radius_ * radius_) {
		its->isHit = false;
		return 0.f; 
	}

	float to_sphere_reflected = sqrtf(radius_ * radius_ - center_distance);
	float distance = to_sphere - to_sphere_reflected;
	float distance_reflected = to_sphere + to_sphere_reflected;

	if (distance > 0.001) {
		its->isHit = true;
		return distance; 
	};

	if (distance_reflected > 0.001) {
		its->isHit = true;
		return distance_reflected;
	};

	its->isHit = false;
	return 0.f;
}

// ----------------------------------------------------------------