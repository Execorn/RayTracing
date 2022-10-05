#include "TRay_.h"

TSceneIntersection_ TRay_::intersect(TScene_& scene){
    Vector3f_ final_point, N;
    TMaterial_ material;
    
    float approximation = 1e10;
    if (std::abs(this->direction_.y_) > .001) { // intersect the ray with the checkerboard, avoid division by zero
        float d = -(this->origin_.y_ + 4) / this->direction_.y_; // the checkerboard plane has equation y_ = -4
        Vector3f_ p = this->origin_ + this->direction_ * d;
        if (d > 0.001 && d < approximation && std::abs(p.x_) < 10 && p.z_ < -10 && p.z_ > -30) {
            approximation = d;
            final_point = p;
            N = {0, 1, 0};
            material.diffuse_color_ = (int(0.5 * final_point.x_ + 1000) + int(0.5 * final_point.z_)) & 1 ? 
                                        Vector3f_{0.3, 0.3, 0.3} : 
                                        Vector3f_{0.3, 0.2, 0.1};
        }
    }
    
    for (const TSphere_ &s : scene.spheres_) { // intersect the ray with all spheres
        TSceneIntersection_ sphere_intersection = {false, {0, 0, 0}};

        float intersect_distance = s.intersection(this->origin_, this->direction_, &sphere_intersection);
        if (!sphere_intersection.isHit || intersect_distance > approximation) {
            continue;
        }

        approximation = intersect_distance;
        final_point = this->origin_ + this->direction_ * approximation;
        
        N = (final_point - s.center_).normalize();
        material = s.material_;
    }

    return {
        approximation < 1000, 
        final_point, 
        N, 
        material };
}

Vector3f_ TRay_::cast_ray(TScene_& scene, const int depth) {
    TSceneIntersection_ current_intersection = this->intersect(scene);
    if (depth > scene.RECURSION_DEPTH_LIMIT_ || !current_intersection.isHit) {
        return scene.background();
    }

    Vector3f_ reflect_dir = current_intersection.reflect_ray(this->direction_, current_intersection.unit_vector).normalize();
    Vector3f_ refract_dir = current_intersection.refract_ray(this->direction_, current_intersection.unit_vector, 
                                                    current_intersection.material.refractive_index_).normalize();

    TRay_ reflected_ray(current_intersection.point, reflect_dir);
    Vector3f_ reflect_color = reflected_ray.cast_ray(scene, depth + 1);

    TRay_ refracted_ray(current_intersection.point, refract_dir);
    Vector3f_ refract_color = refracted_ray.cast_ray(scene, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;

    // lets check if the point is in the shadow
    for (const Vector3f_ &light_src : scene.light_sources_) {
        Vector3f_ light_dir = (light_src - current_intersection.point).normalize();
        TRay_ new_intersection_vector(current_intersection.point, light_dir);
        TSceneIntersection_ new_intersection = new_intersection_vector.intersect(scene);

        if  (new_intersection.isHit && 
            (new_intersection.point - current_intersection.point).len() < (light_src - current_intersection.point).len()) {
                continue;
        }

        diffuse_light_intensity  += std::max(0.f, light_dir * current_intersection.unit_vector);
        specular_light_intensity += std::pow(std::max(0.f, current_intersection.reflect_ray(-light_dir, current_intersection.unit_vector) * 
                                    this->direction_), 
                                    current_intersection.material.specular_exponent_);
    }

    return  current_intersection.material.diffuse_color_ * diffuse_light_intensity * current_intersection.material.albedo_[0]  + 
            Vector3f_{1.0, 1.0, 1.0} * specular_light_intensity * current_intersection.material.albedo_[1]                     +
            reflect_color * current_intersection.material.albedo_[2]                                                           + 
            refract_color * current_intersection.material.albedo_[3];    
}