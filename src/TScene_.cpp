#include "TScene_.h"

// ----------------------------------------------------------------

TSceneIntersection_ TScene_::intersect(const Vector3f_ &src_vector, const Vector3f_ &unit) {
    Vector3f_ final_point, N;
    TMaterial_ material;
    
    float nearest_dist = 1e10;
    if (std::abs(unit.y_) > .001) { // intersect the ray with the checkerboard, avoid division by zero
        float d = -(src_vector.y_ + 4) / unit.y_; // the checkerboard plane has equation y_ = -4
        Vector3f_ p = src_vector + unit * d;
        if (d > 0.001 && d < nearest_dist && std::abs(p.x_) < 10 && p.z_ < -10 && p.z_ > -30) {
            nearest_dist = d;
            final_point = p;
            N = {0, 1, 0};
            material.diffuse_color_ = (int(0.5 * final_point.x_ + 1000) + int(0.5 * final_point.z_)) & 1 ? 
                                        Vector3f_{0.3, 0.3, 0.3} : 
                                        Vector3f_{0.3, 0.2, 0.1};
        }
    }
    
    for (const TSphere_ &s : this->spheres_) { // intersect the ray with all spheres
        TSceneIntersection_ sph_intersect = {false, {0, 0, 0}};

        float intersect_distance = s.intersection(src_vector, unit, &sph_intersect);
        if (!sph_intersect.isHit || intersect_distance > nearest_dist) {
            continue;
        }

        nearest_dist = intersect_distance;
        final_point = src_vector + unit * nearest_dist;
        
        N = (final_point - s.center_).normalize();
        material = s.material_;
    }

    return {
        nearest_dist < 1000, 
        final_point, 
        N, 
        material };
}

// ----------------------------------------------------------------

Vector3f_ TScene_::cast_ray(const Vector3f_ &orig, const Vector3f_ &dir, const int depth) {
    TSceneIntersection_ current_intersection = this->intersect(orig, dir);
    if (depth > RECURSION_DEPTH_LIMIT_ || !current_intersection.isHit)
        return this->background();

    Vector3f_ reflect_dir = current_intersection.reflect_ray(dir, current_intersection.unit_vector).normalize();
    Vector3f_ refract_dir = current_intersection.refract_ray(dir, current_intersection.unit_vector, 
                                                    current_intersection.material.refractive_index_).normalize();
    
    Vector3f_ reflect_color = cast_ray(current_intersection.point, reflect_dir, depth + 1);
    Vector3f_ refract_color = cast_ray(current_intersection.point, refract_dir, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;

    // lets check if the point is in the shadow
    for (const Vector3f_ &light_src : this->light_sources_) {
        Vector3f_ light_dir = (light_src - current_intersection.point).normalize();
        TSceneIntersection_ new_intersection = this->intersect(current_intersection.point, light_dir);

        if  (new_intersection.isHit && 
            (new_intersection.point - current_intersection.point).len() < (light_src - current_intersection.point).len()) {
                continue;
        }

        diffuse_light_intensity  += std::max(0.f, light_dir * current_intersection.unit_vector);
        specular_light_intensity += std::pow(std::max(0.f, current_intersection.reflect_ray(-light_dir, current_intersection.unit_vector) * dir), 
                                             current_intersection.material.specular_exponent_);
    }

    return  current_intersection.material.diffuse_color_ * diffuse_light_intensity * current_intersection.material.albedo_[0]  + 
            Vector3f_{1.0, 1.0, 1.0} * specular_light_intensity * current_intersection.material.albedo_[1]                     +
            reflect_color * current_intersection.material.albedo_[2]                                                           + 
            refract_color * current_intersection.material.albedo_[3];
}

// ----------------------------------------------------------------

void TScene_::trace_scene(int width, int height, float fov, Vector3f_* vector_arr, Tvertex_* vertex_arr) {
#pragma omp parallel for
    for (int current_pixel = 0; current_pixel < width * height; ++current_pixel) {
        float x_direction =  (current_pixel % width + 0.5) -  width / 2.f;

        float y_direction = -(current_pixel / width + 0.5) + height / 2.f; // negate y_direction and flip the image

        float z_direction = -height / (2.f * tan(fov / 2.f));

        vector_arr[current_pixel] = cast_ray(Vector3f_{0, 0, 0}, Vector3f_{x_direction, y_direction, z_direction}.normalize());

        float max = std::max(1.f, std::max(vector_arr[current_pixel][0], std::max(vector_arr[current_pixel][1], vector_arr[current_pixel][2])));

        vertex_arr[current_pixel] = Tvertex_(current_pixel % width, current_pixel / width, 
                                            (RGB_T) (255 * vector_arr[current_pixel][0] / max), 
                                            (RGB_T) (255 * vector_arr[current_pixel][1] / max), 
                                            (RGB_T) (255 * vector_arr[current_pixel][2] / max));
    }
}

// ----------------------------------------------------------------

void TScene_::addMaterial(const std::string new_name, const TMaterial_ new_material) {
    this->materials_[new_name] = new_material;
}

// ----------------------------------------------------------------

void TScene_::addSphere(TSphere_ new_sphere, std::string material_name) {
    if (material_name == "") {
        this->spheres_.push_back(new_sphere);
    } else {
        if (this->materials_.count(material_name) == 0) {
            throw std::invalid_argument("material_name doesn't exist");
        }
        new_sphere.material_ = this->materials_[material_name];

        this->spheres_.push_back(new_sphere);
    }    
}

// ----------------------------------------------------------------

void TScene_::addLightSource(const Vector3f_ new_light_source) {
    this->light_sources_.push_back(new_light_source);
}

// ----------------------------------------------------------------