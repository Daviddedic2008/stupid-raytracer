#include "scene.h"

#include <math.h>

#include "writefile.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


list triangles;
int num_triangles;
list spheres;
int num_spheres;
ray* rays;
uint8_t* brightness;
int numrays;
int w, h;
material sb;
uint8_t tsb;

void init_scene(int sw, int sh, float sx, float sy, material skybox, uint8_t type_sb){
  num_spheres = 0;
  num_triangles = 0;
  triangles = alloc_trianglelist();
  spheres = alloc_spherelist();
  init_reader("color_return.txt");
  rays = (ray*)malloc(sizeof(ray)*(sw*sh));
  numrays = sw*sh;
  brightness = malloc(sizeof(uint8_t)*numrays);
  w = sw;
  h = sh;
  sxw = sx;
  syh = sy;
  sb = skybox;
  tsb = type_sb;
}

void add_rays(float fov){
  int r_n = 0;
  for(int x = -1*(w/2); x < w/2; x++){
    for(int y = -1*(h/2); y < h/2; y++){
      float px = (float)x * sxw/(float)w;
      float py = (float)y * syh/(float)h;
      ray a_r = init_ray(px, py, 0.0F, px * fov, py * fov, 1.0F, 2);
      rays[r_n] = a_r;
      r_n++;
    }
  }
}

void append_triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, material m, unsigned char planar){
  triangle t;
  t.vertice_a.x = x1;
  t.vertice_a.y = y1;
  t.vertice_a.z = z1;
  t.vertice_b.x = x2;
  t.vertice_b.y = y2;
  t.vertice_b.z = z2;
  t.vertice_c.x = x3;
  t.vertice_c.y = y3;
  t.vertice_c.z = z3;
  t.vertice_a.null = 0;
  t.vertice_b.null = 0;
  t.vertice_c.null = 0;
  t.planar = planar;
  t.mat = m;
  add_triangle(&triangles, t);
  num_triangles++;
}

void append_sphere(float cx, float cy, float cz, float radius, material m) {
  sphere s;
  s.center.x = cx;
  s.center.y = cy;
  s.center.z = cz;
  s.radius = radius;
  s.center.null = 0;
  s.mat = m;
  add_sphere(&spheres, s);
  num_spheres++;
}

void pop_triangle(int ind){
  rm_triangle(&triangles, ind);
}

ray bounce_ray_once(ray r) {
  float smallest_dist = MAXFLOAT;
  ray closest_r;
  closest_r.origin.null = 1;
  closest_r.material_touched = sb;
  for(int t = 0; t < triangles.num_elements; t++) {
    ray b = bounce_ray(r, get_triangle(&triangles, t));
    if(b.origin.null == 0 && b.vector.null == 0) {
      float dist = ray_dist(r, b.origin);
      if(dist < smallest_dist) {
        smallest_dist = dist;
        closest_r = b;
      }
    }
  }
  for(int s = 0; s < spheres.num_elements; s++) {
    ray b = bounce_ray_sphere(r, get_sphere(&spheres, s));
    if(b.origin.null == 0 && b.vector.null == 0) {
      float dist = ray_dist(r, b.origin);
      if(dist < smallest_dist) {
        smallest_dist = dist;
        closest_r = b;
      }
    }
  }
  return closest_r;
}

color avg_color(color c1, color c2) {
  color ret;
  ret.r = (c1.r+c2.r)/2;
  ret.g = (c1.g+c2.g)/2;
  ret.b = (c1.b+c2.b)/2;
  return ret;
}

color mean_color(color c1, color c2, int nb) {
  color ret;
  ret.r = ((c1.r) * (nb-1) + c2.r)/nb;
  ret.g = ((c1.g) * (nb-1) + c2.g)/nb;
  ret.b = ((c1.b) * (nb-1) + c2.b)/nb;
  return ret;
}

material blend_materials(material m1, material m2) {
  material ret;
  uint8_t nb = (m1.brightness > m2.brightness) ? m1.brightness : m2.brightness;
  ret.brightness = (nb > 255) ? 255 : nb;
  ret.c = avg_color(m1.c, m2.c);
  return ret;
}

color raypath(ray r, int max_bounces, uint8_t* rb) {
  int c_b = 0;
  list mats = alloc_materiallist();
  while(c_b < max_bounces) {
    r = bounce_ray_once(r);
    if(r.origin.null == 1) {
      r.material_touched = sb;
      if(tsb == 1) {
        add_material(&mats, r.material_touched);
      }
      break;
    }
    if(!(r.material_touched.c.r == sb.c.r && r.material_touched.c.g == sb.c.g && r.material_touched.c.b == sb.c.b)) {
      add_material(&mats, r.material_touched);
    }
  }
  color r_c;
  r_c.r = 0;
  r_c.g = 0;
  r_c.b = 0;
  if(mats.num_elements == 0){goto skpcl;}
  material r_m = get_material(&mats, mats.num_elements-1);
  long int brightness = 0;
  for(int m = mats.num_elements-2; m >= 0; m--) {
    brightness += get_material(&mats, m).brightness;
    r_m = blend_materials(r_m, get_material(&mats, m));
  }
  r_c.r = r_m.c.r * (r_m.brightness/255.0F);
  r_c.g = r_m.c.g * (r_m.brightness/255.0F);
  r_c.b = r_m.c.b * (r_m.brightness/255.0F);
  *rb = r_m.brightness;
  goto skp23;
  skpcl:;
  if(tsb == 0) {
    r_c = sb.c;
  }
  skp23:;
  //printc(r_c);
  free_list(mats);
  return r_c;
}

void printc(color c) {
  printf("R: %d G: %d B: %d\n", c.r, c.g, c.b);
}

color px_color(int px, int py, int repetitions, int max_bounces) {
  ray p_r = rays[py*w + px];
  //color r_c = raypath(p_r, max_bounces);
  color r_c;
  r_c.r = 0;
  r_c.g = 0;
  r_c.b = 0;
  long long int r2 = 0;
  long long int g2 = 0;
  long long int b2 = 0;
  long long int total = 0;
  uint8_t* b = malloc(sizeof(uint8_t));
  for(int r = 0; r < repetitions; r++) {
    srand(time(NULL)+rand());
    color tmp = raypath(p_r, max_bounces, b);
    total += *b;
    r2 += tmp.r;
    g2 += tmp.g;
    b2 += tmp.b;
    r_c = mean_color(r_c, tmp, r+2);
  }
  free(b);
  total /= repetitions/ 2.0F;
  brightness[px+py*w] = (uint8_t)total;
  brightness[px+py*w-1-w] = (uint8_t)total;
  brightness[px+py*w-w] = (uint8_t)total;
  brightness[px+py*w+1-w] = (uint8_t)total;
  brightness[px+py*w-1] = (uint8_t)total;
  brightness[px+py*w+1] = (uint8_t)total;
  brightness[px+py*w-1+w] = (uint8_t)total;
  brightness[px+py*w+w+1+w] = (uint8_t)total;
  r_c.r = r2/repetitions;
  r_c.g = g2/repetitions;
  r_c.b = b2/repetitions;
  return r_c;
}

color* post_processing(float a_alias_strength, color* pxs, int numruns) {
  for(int r = 0; r < numruns; r++) {
    for(int p = 0; p < numrays-1; p++) {
      color c_px = pxs[p];
      uint8_t w_wise = 0;
      if(p%w < w-1) {
        //c_px = mean_color(c_px, pxs[p+1], 2);
        w_wise = 1;
      }
      if((p/w) < h-1) {
        //c_px = mean_color(c_px, pxs[p+w], 2+w_wise);
        ;
      }
      if(p%w < w-1 && p%w > 0 && p/w > 0 && p/w < h) {
        uint8_t t_b = brightness[p];
        uint8_t ul = brightness[p-1-w];
        uint8_t uc = brightness[p-w];
        uint8_t ur = brightness[p+1-w];
        uint8_t ml = brightness[p-1];
        uint8_t mr = brightness[p+1];
        uint8_t bl = brightness[p-1+w];
        uint8_t bc = brightness[p+w];
        uint8_t br = brightness[p+1+w];
        brightness[p] = (ul+uc+ur+ml+mr+bl+bc+br+t_b)/9;

      }
      //pxs[p].r = pxs[p].r * (1.0F-a_alias_strength) + c_px.r * (a_alias_strength);
      //pxs[p].g = pxs[p].g * (1.0F-a_alias_strength) + c_px.g * (a_alias_strength);
      //pxs[p].b = pxs[p].b * (1.0F-a_alias_strength) + c_px.b * (a_alias_strength);
    }
  }
  return pxs;
}

color* get_colors(int rtx_repetitions, int max_bounces) {
  color* ret = malloc(sizeof(color)*numrays);
  for(int x = 0; x < w; x++) {
    for(int y = 0; y < h; y++) {
      ret[y*w + x] = px_color(x, y, rtx_repetitions, max_bounces);
    }
    printf("%d\n", x);
  }
  return ret;
}

void f_return(color* c) {
  for(int c_i = 0; c_i < numrays; c_i++) {
    print_rgb(c[c_i].r, c[c_i].g, c[c_i].b);
  }
}

void offset_all_triangles(float x, float y, float z) {
  for(int t = 0; t < triangles.num_elements; t++) {
    triangle temp = get_triangle(&triangles, t);
    temp.vertice_a.x += x;
    temp.vertice_a.y += y;
    temp.vertice_a.z += z;
    temp.vertice_b.x += x;
    temp.vertice_b.y += y;
    temp.vertice_b.z += z;
    temp.vertice_c.x += x;
    temp.vertice_c.y += y;
    temp.vertice_c.z += z;
    set_triangle(&triangles, t, temp);
  }
}