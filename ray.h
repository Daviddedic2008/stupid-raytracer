//
// Created by Natasa Sesum on 5/12/24.
//

#ifndef RAY_H
#define RAY_H

#endif //RAY_H
#define REF_COEF_AIR 0

typedef struct{
    float x;
    float y;
    float z;
    unsigned char null;
}vec3;

typedef struct{
    float x;
    float y;
    unsigned char null;
}vec2;

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}color;

typedef struct{
    color c;
    unsigned char roughness;
    unsigned char brightness;
    unsigned char transparency;
    unsigned char refrac_coef;
}material;

typedef struct{
    vec3 origin;
    vec3 vector;
    material material_touched;
    unsigned char num_bounces;
    unsigned char in_medium;
    unsigned char prev_refrac_coef;
}ray;

typedef struct{
    vec3 vertice_a;
    vec3 vertice_b;
    vec3 vertice_c;
    material mat;
    unsigned char planar;
}triangle;

typedef struct {
    vec3 center;
    float radius;
    material mat;
}sphere;

typedef struct{
    vec2 vertice_a;
    vec2 vertice_b;
    vec2 vertice_c;
}triangle2D;

int return_sign(float d);
float angle_between_vectors(vec3 v1, vec3 v2);

vec3* init_vector3D(float x, float y, float z);
vec2* init_vector2D(float x, float y);
ray init_ray(float ox, float oy, float oz, float vx, float vy, float vz, int max_bounces);
material init_material(int r, int g, int b, int br, int t, int rh, unsigned char refrac);

material add_materials(material r, material m);

vec2* xy_vector(vec3 v);
vec2* xz_vector(vec3 v);
vec2* zy_vector(vec3 v);
vec3 get_norm(triangle t);


vec2* vector2D_intersection(vec2 v1, vec2 v2, vec2 originv1, vec2 originv2);
vec3* ray_intersection(ray r1, ray r2);
ray bounce_ray(ray r, triangle t, vec3 nv);
ray bounce_ray_sphere(ray r, sphere s, vec3* nv);
float ray_dist(ray r, vec3 d);
int point_in_triangle(vec3 p, triangle t);

void print_3Dvector(vec3 v);

vec3 subtract_3Dvectors_result(vec3 v1, vec3 v2);
vec3 add_vectors_ret(vec3 v1, vec3 v2);
vec3 multiply_3Dvector_by_num_ret(vec3 v, float m);
vec3 multiply_3D_vector_by_vec_ret(vec3 v, vec3 v2);