//
// Created by Natasa Sesum on 5/15/24.
//
#include "scenemake.h"
#include "scene.h"


void add_backplane(unsigned char brightness) {
    material l = init_material(255, 255, 255, 255, 0, 0, 0);
    append_triangle(sxw, syh, -2.0F, sxw, -1.0F*syh, -2.0F, -1.0F*sxw, syh, -2.0F, l, 1);
    append_triangle(-1.0F * sxw, -1.0F * syh, -2.0F, -1.0F * sxw, syh, -2.0F, sxw, -1.0F*syh, -2.0F, l, 1);
}

