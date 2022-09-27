#pragma once
#include <tuple>
#include "TVector_.h"
#include "TMaterial_.h"
#include "TSceneIntersec_.h"

// ----------------------------------------------------------------

class TSphere_ {

public:
	Vector3f_  center_;
	float 	   radius_;
	TMaterial_ material_;

	TSphere_(const Vector3f_ &mid, const float &r, const TMaterial_ &material = {1.5, {0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8},  125.}):
		center_(mid), radius_(r), material_(material) {}

	float intersection(const Vector3f_ &origin, const Vector3f_ &direction, TSceneIntersection_* its) const;
};

// ----------------------------------------------------------------