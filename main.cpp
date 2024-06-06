#include <iostream>

extern "C"{
#include "scenemake.h"
#include "scene.h"
}



int main()
{
    //material sb = init_material(173, 216, 230, 0, 0, 200);
    material sb = init_material(0, 0, 0, 0, 0, 0, 0);
    init_scene(1000, 1000, 240.0F, 240.0F, sb, 0);
    add_rays(0.006F);
    material l2 = init_material(255, 255, 255, 255, 0, 255, 0);
    material r_t = init_material(255, 0, 0, 0, 0, 100, 0);
    material o_t = init_material(255, 165, 0, 0, 0, 100, 0);
    material b_t = init_material(0, 0, 255, 0, 0, 100, 0);
    material bp_t = init_material(191, 64, 191, 0, 0, 80, 0);
    material p_t = init_material(128, 128, 128, 0, 0, 200, 0);
    material rp_t = init_material(255
        , 255, 255, 0, 0, 20, 0);
    material rp_t2 = init_material(255, 255, 255, 0, 255, 20, 150);
    material g_t = init_material(0, 255, 0, 0, 0, 120, 0);
    material y_t = init_material(255, 255, 0, 0, 0, 200, 0);
    material w = init_material(127, 127, 127, 0, 0, 250, 0);
    append_sphere(-20.0F, 50.0F, 100.0F, 50.0F, rp_t);
    append_sphere(60.0F, 0.0F, 60.0F, 20.0F, bp_t);
    append_sphere(30.0F, 0.0F, 30.0F, 29.0F, rp_t2);
    //add_backplane(10);
    append_triangle(-120.0F, -100.0F, 0.0F, -120.0F, -100.0F, 200.0F, 120.0F, -100.0F, 0.0F, l2, 0);
    append_triangle(120.0F, -100.0F, 0.0F, 120.0F, -100.0F, 200.0F, -120.0F, -100.0F, 200.0F, l2, 0);
    append_triangle(-120.0F, -100.0F, 0.0F, -120.0F, 100.0F, 0.0F, -120.0F, -100.0F, 200.0F, r_t, 0);
    append_triangle(-120.0F, 100.0F, 0.0F, -120.0F, 100.0F, 200.0F, -120.0F, -100.0F, 200.0F, r_t, 0);
    append_triangle(120.0F, -100.0F, 0.0F, 120.0F, 100.0F, 0.0F, 120.0F, -100.0F, 200.0F, b_t, 0);
    append_triangle(120.0F, 100.0F, 0.0F, 120.0F, 100.0F, 200.0F, 120.0F, -100.0F, 200.0F, b_t, 0);
    append_triangle(-120.0F, 100.0F, 0.0F, -120.0F, 100.0F, 200.0F, 120.0F, 100.0F, 0.0F, g_t, 0);
    append_triangle(120.0F, 100.0F, 0.0F, 120.0F, 100.0F, 200.0F, -120.0F, 100.0F, 200.0F, g_t, 0);
    append_triangle(-120.0F, -100.0F, 200.0F, -120.0F, 100.0F, 200.0F, 120.0F, -100.0F, 200.0F, o_t, 0);
    append_triangle(-120.0F, 100.0F, 200.0F, 120.0F, 100.0F, 200.0F, 120.0F, -100.0F, 200.0F, o_t, 0);
    append_triangle(0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 1.0F, 0.0F, 0.0F, w, 1);
    offset_all_triangles(0.0F, 0.0F, -30.0F);
    get_normals();
    f_return(post_processing(1.0F, get_colors(200, 4), 0));
    return 0;
}
