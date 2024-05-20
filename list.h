//
// Created by Natasa Sesum on 5/12/24.
//

#ifndef LIST_H
#define LIST_H

#endif //LIST_H
#include "ray.h"

typedef struct{
    void* elements;
    int num_elements;
    int size_element;
}list;

list new_list(int elem_size);

void free_list(list l);

void* general_get(list* l, int index);

void general_add(list* l, void* el);

list alloc_intlist();

void add_int(list* l, int el);

void rm_int(list* l, int ind);

int get_int(list* l, int ind);

void set_int(list* l, int ind, int val);

int find_int(list* l, int val);

void int_insertion_sort(list* l, int dir);

void print_int_list(list* l);

list alloc_trianglelist();

void add_triangle(list* l, triangle el);

void rm_triangle(list* l, int ind);

triangle get_triangle(list* l, int ind);

void set_triangle(list* l, int ind, triangle val);

int find_triangle(list* l, triangle val);

int cp_triangles(void* i1, void* i2);

void triangle_insertion_sort(list* l, int dir);

void print_triangle_list(list* l);

list alloc_doublelist();

void add_double(list* l, double el);

void rm_double(list* l, double ind);

double get_double(list* l, int ind);

void set_double(list* l, int ind, double val);

int find_double(list* l, double val);

int cp_doubles(void* i1, void* i2);

void double_insertion_sort(list* l, int dir);

void print_double_list(list* l);

list alloc_raylist();

void add_ray(list* l, ray el);

void rm_ray(list* l, double ind);

ray get_ray(list* l, int ind);

void set_ray(list* l, int ind, ray val);

int find_ray(list* l, ray val);

int cp_rays(void* x1, void* x2, vec3 origin);

void ray_insertion_sort(list* l, int dir, vec3 origin);

void print_ray_list(list* l);

list alloc_materiallist();

void add_material(list* l, material el);

void rm_material(list* l, int ind);

material get_material(list* l, int ind);

void set_material(list* l, int ind, material val);

int find_material(list* l, material val);

void print_material_list(list* l);

ray* get_ray_addr(list* l, int ind);

list alloc_spherelist();

void add_sphere(list* l, sphere el);

void rm_shpere(list* l, int ind);

sphere get_sphere(list* l, int ind);

void set_sphere(list* l, int ind, sphere val);

int find_sphere(list* l, sphere val);

int cp_spheres(void* i1, void* i2);

void sphere_insertion_sort(list* l, int dir);

void print_sphere_list(list* l);
