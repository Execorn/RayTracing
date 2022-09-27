#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "TScene_.h"

// ----------------------------------------------------------------

const int TRACER_WIDTH  = 1024;
const int TRACER_HEIGHT =  768;

int main() {
    TWindow_ window(TRACER_WIDTH, TRACER_HEIGHT, "RayTracing!");

    Vector3f_*  vector_arr = new   Vector3f_[TRACER_WIDTH * TRACER_HEIGHT];
    Tvertex_*   vertex_arr = new    Tvertex_[TRACER_WIDTH * TRACER_HEIGHT];

    TScene_ ray_tracing_scene;

    ray_tracing_scene.addLightSource({-20,  20,  20});
    ray_tracing_scene.addLightSource({ 30,  50, -25});
    ray_tracing_scene.addLightSource({ 30,  20,  30});

    ray_tracing_scene.addMaterial("ivory",      {1.0, {0.9,  0.5, 0.1, 0.0}, {0.4, 0.4, 0.3},   50.});       
    ray_tracing_scene.addMaterial("glass",      {1.5, {0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8},  125.});
    ray_tracing_scene.addMaterial("red_rubber", {1.0, {1.4,  0.3, 0.0, 0.0}, {0.3, 0.1, 0.1},   10.});
    ray_tracing_scene.addMaterial("mirror",     {1.0, {0.0, 16.0, 0.8, 0.0}, {1.0, 1.0, 1.0}, 1425.});

    ray_tracing_scene.addSphere({{-3,    0,   -16}, 2, {}}, "ivory");
    ray_tracing_scene.addSphere({{-1.0, -1.5, -12}, 2, {}}, "glass");
    ray_tracing_scene.addSphere({{ 1.5, -0.5, -18}, 3, {}}, "red_rubber");
    ray_tracing_scene.addSphere({{ 7,    5,   -18}, 4, {}}, "mirror");


    while (window.isOpen()) {
        TEvent_ main_event;
		while (window.getPollEvent(&main_event) != 0) {
			if (main_event.event_type == TEvent_::Type::windowClosed) {
				window.close();
            }
        }

        ray_tracing_scene.trace_scene(TRACER_WIDTH, TRACER_HEIGHT, 1.05f, vector_arr, vertex_arr);

        TColor_ background(0, 0, 0);
        window.clear(background);
        window.render(vertex_arr, TRACER_WIDTH * TRACER_HEIGHT);

        window.display();
    }

    delete[] vertex_arr;
    
    return 0;
}

// ----------------------------------------------------------------