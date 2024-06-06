#include "list.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//makroi
#define false 0
#define true 1
#define positive 1
#define zero 0
#define vx(v) v.x
#define vy(v) v.y
#define vz(v) v.z
#define sv(v, tx, ty, tz) v.x = tx; v.y = ty; v.z = tz;


// generalne funkcije
int return_sign(float d){
  if(d == 0.0){
    return zero;
  }
  return (d > 0.0F) ? 1 : 0;
}

float fast_invsqrt(float f) {
  float th = 1.5F;
  float h = f * 0.5F;
  long temp = *((long*)&f);
  temp = 0x5f3759df - ( temp >> 1 );
  float temp2 = *((float*)&temp);
  temp2 = temp2 * (th-(h * temp2*temp2));
  return temp2;
}

float rad_to_deg(float r){
  return r * 180.0 * 7.0/22.0;
}

material add_materials(material r, material m){
  material ret;
  uint8_t brightness_diff = r.brightness-m.brightness;
  float d = ((float)(brightness_diff)/255.0F);
  ret.brightness = r.brightness + m.brightness - (r.brightness + m.brightness>0);
  ret.c.r = r.c.r * d + (1.0-d) * m.c.r;
  ret.c.g = r.c.g * d + (1.0-d) * m.c.g;
  ret.c.b = r.c.b * d + (1.0-d) * m.c.b;
  return ret;
}

material init_material(int r, int g, int b, int br, int t, int rh, unsigned char refrac) {
  material ret;
  ret.c.r = r;
  ret.c.g = g;
  ret.c.b = b;
  ret.brightness = br;
  ret.transparency = t;
  ret.roughness = rh;
  ret.refrac_coef = refrac;
  return ret;
}

void print_3Dvector(vec3 v){
  if(v.null == true){
    printf("%s\n", "null vector");
    return;
  }
  printf("%s", "X: ");
  printf("%f", v.x);
  printf("%s", "   ");
  printf("%s", "Y: ");
  printf("%f", v.y);
  printf("%s", "   ");
  printf("%s", "Z: ");
  printf("%f", v.z);
  printf("%s\n", "   ");
}

void set_vec(vec3* v, float x, float y, float z){
  v->x = x;
  v->y = y;
  v->z = z;
}

vec3 flip_vec(vec3 v){
  v.x = -1.0*v.x;
  v.y = -1.0*v.y;
  v.z = -1.0*v.z;
  return v;
}

void subtract_3Dvectors(vec3* v1, vec3 v2){
  v1->x -= v2.x;
  v1->y -= v2.y;
  v1->z -= v2.z;
}

vec3 subtract_3Dvectors_result(vec3 v1, vec3 v2){
  vec3 ret;
  ret.x = v1.x-v2.x;
  ret.y = v1.y-v2.y;
  ret.z = v1.z-v2.z;
  return ret;
}

vec3* ret_subtract_3Dvectors(vec3 v1, vec3 v2){
  vec3* v = malloc(sizeof(vec3));
  v->x = v1.x - v2.x;
  v->y = v1.y - v2.y;
  v->z = v1.z - v2.z;
  return v;
}

void add_3Dvectors(vec3* v1, vec3 v2){
  v1->x += v2.x;
  v1->y += v2.y;
  v1->z += v2.z;
}

vec3 add_vectors_ret(vec3 v1, vec3 v2){
  v1.x += v2.x;
  v1.y += v2.y;
  v1.z += v2.z;
  return v1;
}

void multiply_3Dvector_by_num(vec3* v, float m){
  v->x *= m;
  v->y *= m;
  v->z *= m;
}

vec3 multiply_3Dvector_by_num_ret(vec3 v, float m){
  v.x *= m;
  v.y *= m;
  v.z *= m;
  return v;
}

vec3 multiply_3D_vector_by_vec_ret(vec3 v, vec3 v2){
  v.x *= v2.x;
  v.y *= v2.y;
  v.z *= v2.z;
  return v;
}

float dist_between_vec(vec3 v1, vec3 v2){
  return sqrt(pow(v2.z-v1.z, 2) + pow(v2.y-v1.y, 2) + pow(v2.x-v1.x, 2));
}

float matrix2D(float d1, float d2, float d21, float d22){
  return d1 * d22 - d2 * d21;
}

vec3 cross(vec3 a, vec3 b){
  vec3 ret;
  ret.x = matrix2D(a.y, a.z, b.y, b.z);
  ret.y = matrix2D(a.x, a.z, b.x, b.z);
  ret.z = matrix2D(a.x, a.y, b.x, b.y);
  ret.null = false;
  return ret;
}

float dot(vec3 a, vec3 b){
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float calc_magnitude(vec3 v){
  return fast_invsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 normalize_vector(vec3 v){
  vec3 ret;
  float d = calc_magnitude(v);
  ret.x = v.x * d;
  ret.y = v.y * d;
  ret.z = v.z * d;
  ret.null = false;
  return ret;
}

float angle_between_vectors(vec3 v1, vec3 v2){
  float t = dot(v1, v2) * (calc_magnitude(v2)*calc_magnitude(v1));
  return rad_to_deg(acos(t));
}

//inicializacije za vektore
vec3* init_vector3D(float x, float y, float z){
  vec3* ret = malloc(sizeof(vec3));
  set_vec(ret, x, y, z);
  ret->null = false;
  return ret;
}

vec2* init_vector2D(float x, float y){
  vec2* ret = malloc(sizeof(vec2));
  ret->x = x;
  ret->y = y;
  ret->null = false;
  return ret;
}

// inicializacija za zrake
ray init_ray(float ox, float oy, float oz, float vx, float vy, float vz, int max_bounces){
  ray ret;
  set_vec(&(ret.origin), ox, oy, oz);
  set_vec(&(ret.vector), vx, vy, vz);
  ret.material_touched.brightness = 0;
  ret.material_touched.c.r = 0;
  ret.material_touched.c.g = 0;
  ret.material_touched.c.b = 0;
  ret.in_medium = false;
  ret.prev_refrac_coef = REF_COEF_AIR;
  return ret;
}

// ini

// nalazenje planarnih vektora 3d vektora i 3d trougao -> 2d trougao
vec2* xy_vector(vec3 v){
  vec2* r = malloc(sizeof(vec2));
  r->x = v.x/v.z;
  r->y = v.y/v.z;
  return r;
}
vec2* xz_vector(vec3 v){
  vec2* r = malloc(sizeof(vec2));
  r->x = v.x/v.y;
  r->y = v.z/v.y;
  return r;
}
vec2* zy_vector(vec3 v){
  vec2* r = malloc(sizeof(vec2));
  r->x = v.z/v.x;
  r->y = v.y/v.x;
  return r;
}

triangle2D* planarize_triangle(triangle*t, vec3 nv){
  triangle2D* ret = malloc(sizeof(triangle2D));
  ret->vertice_a.x = (nv.z > nv.x && nv.z > nv.y) ? t->vertice_a.x/t->vertice_a.z : (nv.x > nv.z && nv.x > nv.y) ? t->vertice_a.z/t->vertice_a.x : (nv.y > nv.x && nv.y > nv.z) ? t->vertice_a.x/t->vertice_a.y : false;
  ret->vertice_a.y = (nv.z > nv.x && nv.z > nv.y) ? t->vertice_a.y/t->vertice_a.z : (nv.x > nv.z && nv.x > nv.y) ? t->vertice_a.y/t->vertice_a.x : (nv.y > nv.x && nv.y > nv.z) ? t->vertice_a.z/t->vertice_a.y : false;
  return ret;
}

int point_in_triangle(vec3 p, triangle t) {
  t.vertice_a = subtract_3Dvectors_result(t.vertice_a, p);
  t.vertice_b = subtract_3Dvectors_result(t.vertice_b, p);
  t.vertice_c = subtract_3Dvectors_result(t.vertice_c, p);
  vec3 c1 = cross(t.vertice_b, t.vertice_a);
  vec3 c2 = cross(t.vertice_a, t.vertice_c);
  vec3 c3 = cross(t.vertice_c, t.vertice_b);
  if(dot(c1, c2) <= 0.0F) {
    return false;
  }
  if(dot(c1, c3) <= 0.0F) {
    return false;
  }
  return true;
}

uint8_t same_dir(vec3 v1, vec3 v2) {
  return return_sign(v1.x) == return_sign(v2.x) && return_sign(v1.y) == return_sign(v2.y) && return_sign(v1.z) == return_sign(v2.z);
}

uint8_t point_on_ray(ray r, vec3 p) {
  vec3 vec_rayp = subtract_3Dvectors_result(p, r.origin);
  if((fabs(subtract_3Dvectors_result(r.origin, p).x) + fabs(subtract_3Dvectors_result(r.origin, p).y) + fabs(subtract_3Dvectors_result(r.origin, p).z)) > 0.1F) {
    return same_dir(r.vector, vec_rayp);
  }
  return false;
}

vec3 get_norm(triangle t) {
  vec3 ab = subtract_3Dvectors_result(t.vertice_a, t.vertice_b);
  vec3 bc = subtract_3Dvectors_result(t.vertice_b, t.vertice_c);
  vec3 normalized_vector = cross(ab, bc);
  return normalize_vector(normalized_vector);
}

// presek izmedu vektora i ravne
// vrati normalan vektor ravne u norm_v
vec3 triangle_ray_intersection(ray r, triangle t, vec3 norm_v){
  vec3 ret;
  ret.null = false;
  
  // prvo parametrizujemo vektor
  float ox = r.origin.x;
  float oy = r.origin.y;
  float oz = r.origin.z;

  vec3 norm_ray = r.vector;
  float dx = norm_ray.x;
  float dy = norm_ray.y;
  float dz = norm_ray.z;

  float xdist = dx-ox;
  float ydist = dy-oy;
  float zdist = dz-oz;

  /* parametrizovan vektor:
   x = ox + t * xdist
   y = oy + t * ydist
   z = oz + t * zdist
  */

  //normalizovan vektor ravne:
  // A-B x C-B
  //print_3Dvector(bc);

  /*tu se izracuna cross
    i = (1, 0, 0)
    j = (0, 1, 0)
    k = (0, 0, 1)

    matrica(racunamo discriminant):
    i    j    k   
    abx  aby  abz
    bcx  bcy  bcz

    uprostena matrica:

    i * ((aby*bcz) - (bcy * abz)) - j * ((abx*bcz) - (bcx * abz)) + k * ((abx*bcy) - (bcx * aby))
  */
  vec3 normalized_vector = norm_v;
  /*normalized_vector = nv
  a je tacka na ravni
  jednacina ravne: nvx * (x-ax) + nvy* (y-ay) + nvz*(z-az) = 0
  */
  float ax = t.vertice_a.x;
  float ay = t.vertice_a.y;
  float az = t.vertice_a.z;
  /* zameni vektor (x, y, z) sa (ox+t*xdist, oy+t*ydist, oz+t*zdist)
  resi za t
  nvx*(ox+t*xdist-ax)+nvy*(oy+t*ydist-ay)+nvz*(oz+t*zdist-az) = 0
  nvx*ox-nvx*ax+nvy*oy-nvy*ay+nvz*oz-nvz*az = 0
  nvx*t*xdist+nvy*t*ydist+nvz*t*zdist=nvx*ox-nvx*ax+nvy*oy-nvy*ay+nvz*oz-nvz*az
  t*(nvx*xdist+nvy*ydist+nvz*zdist) = nvx*ox-nvx*ax+nvy*oy-nvy*ay+nvz*oz-nvz*az
  t = (nvx*ox-nvx*ax+nvy*oy-nvy*ay+nvz*oz-nvz*az)/(nvx*xdist+nvy*ydist+nvz*zdist)
  */
  normalized_vector = normalize_vector(normalized_vector);
  float tmp_f = dot(r.vector, normalized_vector);
  if(tmp_f == 0.0F) {
    ret.null = true;
    return ret;
  }
  float p_t = dot(subtract_3Dvectors_result(t.vertice_a, r.origin), normalized_vector) / tmp_f;
  set_vec(&ret, r.origin.x + (r.vector.x * p_t), r.origin.y + (r.vector.y * p_t), r.origin.z + (r.vector.z * p_t));
  if(t.planar){goto skptri;}
  if(!point_in_triangle(ret, t)){
    ret.null = true;
    return ret;
  }
  skptri:
  ret.null = false;
  return ret;
}

float ray_dist(ray r, vec3 d){
  return(dist_between_vec(d, r.origin));
}

ray bounce_ray(ray r, triangle t, vec3 nv){
  ray ret;
  vec3 intersect = triangle_ray_intersection(r, t, nv);
  if(!point_on_ray(r, intersect)) {
    ret.origin.null = true;
    ret.vector.null = true;
    return ret;
  }
  vec3 normalized_line_of_reflection = normalize_vector(nv);
  float temp = dot(normalized_line_of_reflection, r.vector)*(calc_magnitude(r.vector)*calc_magnitude(normalized_line_of_reflection));
  float angle_between_ray_and_nlr = rad_to_deg(acos(temp));
  //printf("%f\n", calc_magnitude(normal_vec));
  if(angle_between_ray_and_nlr > 90.0) {
    normalized_line_of_reflection = flip_vec(normalized_line_of_reflection);
  }
  vec3 rand_vec;
  rand_vec.x =  ((rand()%100)/99.0 - 0.5)*2.0;
  rand_vec.y =  ((rand()%100)/99.0 - 0.5)*2.0;
  rand_vec.z =  ((rand()%100)/99.0 - 0.5)*2.0;
  float a1 = angle_between_vectors(rand_vec, normalized_line_of_reflection);
  float a2 = angle_between_vectors(normalized_line_of_reflection, rand_vec);
  float sa = (a1 < a2) ? a1 : a2;


  while(true){
    rand_vec.x =  ((rand()%100)/99.0 - 0.5)*2.0;
    rand_vec.y =  ((rand()%100)/99.0 - 0.5)*2.0;
    rand_vec.z =  ((rand()%100)/99.0 - 0.5)*2.0;
    a1 = angle_between_vectors(rand_vec, normalized_line_of_reflection);
    a2 = angle_between_vectors(normalized_line_of_reflection, rand_vec);
    sa = (a1 < a2) ? a1 : a2;
    if(sa < 90.0){
      break;
    }
  }
  //w = v - 2 * (v ∙ n) * n
  float dt = dot(normalized_line_of_reflection, normalized_line_of_reflection);
  vec3 reflected_vec = subtract_3Dvectors_result(r.vector, multiply_3Dvector_by_num_ret(normalized_line_of_reflection, dt*2));
  reflected_vec = add_vectors_ret(multiply_3Dvector_by_num_ret(reflected_vec, (1.0F-t.mat.roughness/255.0F)), multiply_3Dvector_by_num_ret(rand_vec, (t.mat.roughness/255.0F)));
  if(intersect.null == false){
    ret.vector = reflected_vec;
    ret.origin = intersect;
    ret.vector.null = false;
    //ret.origin.null = false;
    ret.material_touched = t.mat;
    return ret;
  }
  ret.origin.null = true;
  ret.vector.null = true;
  return ret;
}








vec3 sphere_intersect(ray ra, sphere cs) {
  vec3 ret;
  ret.null = false;
  /* jednacina zraka/vektora: f(t) = origin + t*vec
   * deo x: fx(t)= originx + vecx*t
   * deo y: fy(t)= originy + vecy*t
   * deo z: fz(t)= originz + vecz*t
   * dist formula kruga: sqrt((pointx-centerx)^2 + (pointy-centery)^2 + (pointz-centerz)^2) = d
   * zameni point sa (fx, fy, fz)
   * d = r^2
   * sqrt((originx+vecx*t-centerx)^2 + (originy+vecy*t-centery)^2 + (originz+vecz*t-centerz)^2) = r^2
   * sqrt(originx^2 + originx*vecx*t - originx*centerx + vecx*t*originx + (vecx*t)^2 - vecx*t*centerx - centerx*originx - centerx*vecx*t + centerx^2 + originy^2 + originy*vecy*t - originy*centery + vecy*t*originy + (vecy*t)^2 - vecy*t*centery - centery*originy - centery*vecy*t + centery^2 + originz^2 + originz*vecz*t - originz*centerz + vecz*t*originz + (vecz*t)^2 - vecz*t*centerz - centerz*originz - centerz*vecz*t + centerz^2) = r^2
   * t terms: originx^2-originx*centerx-centerx*originx+centerx^2+originy^2-originy*centery-centery*originy+centery^2+originz^2-originz*centerz-centerz*originz+centerz^2
   * originx*vecx*t + vecx*t*origin + vecx^2*t^2 - vecx*t*centerx - centerx*vecx*t +originy*vecy*t + vecy*t*originy + vecy^2*t^2 - vecy*t*centery - cecentery*vecy*t + originz*vecz*t+vecz*t*originz + vecz^2*t^2 - vecz*t*centerz - centerz*vecz*t
   *
   * -1*(originx^2-originx*centerx-centerx*originx+centerx^2+originy^2-originy*centery-centery*originy+centery^2+originz^2-originz*centerz-centerz*originz+centerz^2) + r^4 = originx*vecx*t + vecx*t*origin + vecx^2*t^2 - vecx*t*centerx - centerx*vecx*t +originy*vecy*t + vecy*t*originy + vecy^2*t^2 - vecy*t*centery - cecentery*vecy*t + originz*vecz*t+vecz*t*originz + vecz^2*t^2 - vecz*t*centerz - centerz*vecz*t
   * (-1*(originx^2-originx*centerx-centerx*originx+centerx^2+originy^2-originy*centery-centery*originy+centery^2+originz^2-originz*centerz-centerz*originz+centerz^2) + r^4)/t =
   * a = vecx^2 + vecy^2 + vecz^2
   * b = originx*vecx+originy*vecy + originz*vecz - 2*vecx*centerx - 2*vecy*centery - 2*vecz*centerz
   * c = originx*originx - 2*originx*centerx+centerx*centerx+originy*originy-2*originy*centery+centery*centery+originz*originz-2*originz*centerz+centerz*centerz+r*r*r*r
   * t = -1*b+-(sqrt(b*b-4*a*c)/2*a)
  */
  float cx = cs.center.x;
  float cy = cs.center.y;
  float cz = cs.center.z;

  float px = ra.origin.x;
  float py = ra.origin.y;
  float pz = ra.origin.z;

  float vx = ra.vector.x;
  float vy = ra.vector.y;
  float vz = ra.vector.z;

  float a = vx * vx + vy * vy + vz * vz;
  float b = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
  float c = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
             pz * pz - 2 * pz * cz + cz * cz - cs.radius * cs.radius;
  float disc = b*b - 4*a*c;
  if(disc < 0.0) {
    ret.null = true;
    return ret;
  }
  float sq = sqrtf(disc);
  float t1 = (-1*b + sq)/(2*a);
  if(disc == 0) {
    ret.x = ra.origin.x + ra.vector.x * t1;
    ret.y = ra.origin.y + ra.vector.y * t1;
    ret.z = ra.origin.z + ra.vector.z * t1;
  }
  float t2 = (-1*b - sq)/(2*a);
  ret.x = ra.origin.x + ra.vector.x  *  ((t1 < t2) ? t1 : t2);
  ret.y = ra.origin.y + ra.vector.y  *  ((t1 < t2) ? t1 : t2);
  ret.z = ra.origin.z + ra.vector.z  *  ((t1 < t2) ? t1 : t2);
  return ret;
}

ray bounce_ray_sphere(ray r, sphere s, vec3* nv){
  ray ret;
  vec3 intersect = sphere_intersect(r, s);
  if(intersect.null || !point_on_ray(r, intersect)) {
    ret.origin.null = true;
    ret.vector.null = true;
    return ret;
  }
  vec3 normal_vec = subtract_3Dvectors_result(intersect, s.center);
  normal_vec.null = false;
  vec3 normalized_line_of_reflection = flip_vec(normalize_vector(normal_vec));
  *nv = normalized_line_of_reflection;
  vec3 rand_vec;
  float a1;
  float a2;
  float sa;
  while(true) {
    rand_vec.x =  ((rand()%100)/99.0 - 0.5)*2.0;
    rand_vec.y =  ((rand()%100)/99.0 - 0.5)*2.0;
    rand_vec.z =  ((rand()%100)/99.0 - 0.5)*2.0;
    a1 = angle_between_vectors(rand_vec, normalized_line_of_reflection);
    a2 = angle_between_vectors(normalized_line_of_reflection, rand_vec);
    sa = (a1 < a2) ? a1 : a2;
    if(sa < 90.0){
      break;
    }
  }
  float dt = dot(normalized_line_of_reflection, normalized_line_of_reflection);
  vec3 reflected_vec = subtract_3Dvectors_result(r.vector, multiply_3Dvector_by_num_ret(normalized_line_of_reflection, dt*2));
  reflected_vec = add_vectors_ret(multiply_3Dvector_by_num_ret(reflected_vec, (1.0F-s.mat.roughness/255.0F)), multiply_3Dvector_by_num_ret(rand_vec, (s.mat.roughness/255.0F)));
  if(intersect.null == false){
    ret.vector = reflected_vec;
    ret.origin = intersect;
    ret.vector.null = false;
    ret.material_touched = s.mat;
    return ret;
  }
  ret.origin.null = true;
  ret.vector.null = true;
  return ret;
}