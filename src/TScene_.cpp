#include "TScene_.h"
#include "TRay_.h"

// ----------------------------------------------------------------

void TScene_::trace_scene(int width, int height, float fov, Vector3f_* vector_arr, Tvertex_* vertex_arr) {
#pragma omp parallel for
    for (int current_pixel = 0; current_pixel < width * height; ++current_pixel) {
        float x_direction =  (current_pixel % width + 0.5) -  width / 2.f;

        float y_direction = -(current_pixel / width + 0.5) + height / 2.f; // negate y_direction and flip the image

        float z_direction = -height / (2.f * tan(fov / 2.f));

        TRay_ cur_pixel_ray(Vector3f_{0, 0, 0}, Vector3f_{x_direction, y_direction, z_direction}.normalize()); 
        vector_arr[current_pixel] = cur_pixel_ray.cast_ray(*this);

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