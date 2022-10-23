#pragma once 

#include <vector>
#include <map>

#include "TVector_.h"
#include "TMaterial_.h"
#include "TSphere_.h"
#include "TWindow_.h"
#include "TVertex_.h"
#include "TSceneIntersec_.h"
#include "TPlane_.h"


class TRay_;

class TScene_ {

    friend TRay_;
private:

    Vector3f_ background_color_ = {0.51, 0.8, 0.51};

    // map: material_name - material
    std::map<std::string, TMaterial_> materials_;

    std::vector<TSphere_> spheres_;

    std::vector<Vector3f_> light_sources_;
    
    std::vector<TPlane_> planes_;

public:

    TScene_() {};

    const int RECURSION_DEPTH_LIMIT_ = 5;
    
    Vector3f_ background() const { return this->background_color_; }

    void setBackgroundColor(const Vector3f_ new_color) { background_color_ = new_color; }

    void addMaterial(const std::string new_name, const TMaterial_ new_material);

    void addSphere(TSphere_ new_sphere, std::string material_name = ""); 

    void addPlane(TPlane_ new_plane, std::string material_name = "");

    void addLightSource(const Vector3f_ new_light_source);

    // ray tracing function

    void trace_scene(int width, int height, float fov, Vector3f_* vector_arr, Tvertex_* vertex_arr);
};