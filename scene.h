//
// Created by Natasa Sesum on 5/12/24.
//

#ifndef SCENE_H
#define SCENE_H

#endif //SCENE_H
#include "list.h"

float sxw, syh;

void init_scene(int sw, int sh, float sx, float sy, material skybox, unsigned char type_sb);

void printc(color c);

void append_triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, material m, unsigned char planar);

void append_sphere(float cx, float cy, float cz, float radius, material m);

void add_rays(float fov);

color* post_processing(float a_alias_strength, color* pxs, int numruns);

void pop_triangle(int ind);

color* get_colors(int rtx_repetitions, int max_bounces);

void f_return(color* c);

void offset_all_triangles(float x, float y, float z);

