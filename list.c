#include "list.h"
#include <stdlib.h>
#include <stdio.h>

list new_list(int elem_size){
  list ret;
  ret.size_element = elem_size;
  ret.elements = malloc(0);
  ret.num_elements = 0;
  return ret;
}

void free_list(list l) {
  free(l.elements);
}

void* general_get(list* l, int index){
  void* ret = (void*)((char*)l->elements + index * l->size_element);
  return ret;
}

void general_add(list* l, void* el){
  void* temp = malloc(l->size_element * (l->num_elements+1));
  for(int e = 0; e < l->num_elements * l->size_element; e++){
    ((u_int8_t*)temp)[e] = ((u_int8_t*)l->elements)[e];
  }
  for(int e = 0; e < l->size_element; e++){
    ((u_int8_t*)temp)[(l->num_elements)*l->size_element+e] = ((u_int8_t*)el)[e];
  }
  free(l->elements);
  l->elements = temp;
  l->num_elements++;
}

void general_rm(list* l, int ind){
  void* temp = malloc(l->size_element * (l->num_elements-1));
  for(int e = 0, e3 = 0; e < l->num_elements; e++){
    if(e == ind){
      goto skp;
    }
    for(int e2 = 0; e2 < l->size_element; e2++){
      ((char*)temp)[e3*l->size_element + e2] = ((char*)l->elements)[e*l->size_element + e2];
    }
    e3++;
    skp:;
  }
  free(l->elements);
  l->elements = temp;
  l->num_elements--;
} 

void general_set(list* l, int ind, void* val){
  for(int e = 0; e < l->num_elements; e++){
    if(e != ind){
      goto skp;
    }
    for(int e2 = 0; e2 < l->size_element; e2++){
      ((char*)l->elements)[e*l->size_element + e2] = ((char*)val)[e2];
    }
    skp:;
  }
}

int general_find(list* l, void* val){
  for(int e = 0; e < l->num_elements; e++){
    unsigned char found = 1;
    for(int e2 = 0; e2 < l->size_element; e2++){
      if(((char*)l->elements)[e*l->size_element + e2] != ((char*)val)[e2]){
        goto skp;
      }
    }
    return e;
    skp:;
  }
  return -1;
}

void general_insertion_sort(list* l, int (*cmp_func)(void*, void*), int dir){
  for(int e1 = 0; e1 < l->num_elements; e1++){
    void* best_val = general_get(l, e1);
    int best_index = e1;
    for(int e2 = e1+1; e2 < l->num_elements; e2++){
      void* c_val = general_get(l, e2);
      best_index = (cmp_func(c_val, best_val) == dir) ? e2 : best_index;
      best_val = (cmp_func(c_val, best_val) == dir) ? c_val : best_val;
    }
    void* f_v = general_get(l, e1);
    void* f_val = malloc(sizeof(l->size_element));
    for(int c = 0; c < l->size_element; c++){
      ((char*)f_val)[c] = ((char*)f_v)[c];
    }
    general_set(l, e1, best_val);
    general_set(l, best_index, f_val);
    free(f_val);
  }
}



//INT LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(int)

list alloc_intlist(){
  list ret = new_list(4);
  return ret;
}

void add_int(list* l, int el){
  general_add(l, &el);
}

void rm_int(list* l, int ind){
  general_rm(l, ind);
}

int get_int(list* l, int ind){
  return *((int*)general_get(l, ind));
}

void set_int(list* l, int ind, int val){
  void* i = malloc(sizeof(int));
  *((int*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_int(list* l, int val){
  void* v = malloc(sizeof(int));
  *((int*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

int cp_ints(void* i1, void* i2){
  return (*((int*)i1) > *((int*)i2)) ? 1 : (*((int*)i1) < *((int*)i2)) ? -1 : 0;
}

void int_insertion_sort(list* l, int dir){
  general_insertion_sort(l, cp_ints, -1*dir);
}

void print_int_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%d\n", get_int(l, e));
  }
}




//TRIANGLE LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(triangle)

list alloc_trianglelist(){
  list ret = new_list(sizeof(triangle));
  return ret;
}

void add_triangle(list* l, triangle el){
  general_add(l, &el);
}

void rm_triangle(list* l, int ind){
  general_rm(l, ind);
}

triangle get_triangle(list* l, int ind){
  return *((triangle*)general_get(l, ind));
}

void set_triangle(list* l, int ind, triangle val){
  void* i = malloc(sizeof(triangle));
  *((triangle*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_triangle(list* l, triangle val){
  void* v = malloc(sizeof(triangle));
  *((triangle*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

int cp_triangles(void* i1, void* i2){
  return (*((int*)i1) > *((int*)i2)) ? 1 : (*((int*)i1) < *((int*)i2)) ? -1 : 0;
}

void triangle_insertion_sort(list* l, int dir){
  general_insertion_sort(l, cp_ints, -1*dir);
}

void print_triangle_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%s\n", "v_a: x:");
    printf("%f", get_triangle(l, e).vertice_a.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_a.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_a.z);
    printf("%s\n", "v_b: x:");
    printf("%f", get_triangle(l, e).vertice_b.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_b.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_b.z);
    printf("%s\n", "v_c: x:");
    printf("%f", get_triangle(l, e).vertice_c.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_c.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_c.z);
  }
}



//DOUBLE LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(double)

list alloc_doublelist(){
  list ret = new_list(sizeof(double));
  return ret;
}

void add_double(list* l, double el){
  general_add(l, &el);
}

void rm_double(list* l, double ind){
  general_rm(l, ind);
}

double get_double(list* l, int ind){
  return *((double*)general_get(l, ind));
}

void set_double(list* l, int ind, double val){
  void* i = malloc(sizeof(double));
  *((double*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_double(list* l, double val){
  void* v = malloc(sizeof(double));
  *((double*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

int cp_doubles(void* i1, void* i2){
  return (*((double*)i1) > *((double*)i2)) ? 1 : (*((double*)i1) < *((double*)i2)) ? -1 : 0;
}

void double_insertion_sort(list* l, int dir){
  general_insertion_sort(l, cp_doubles, -1*dir);
}

void print_double_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%f\n", get_double(l, e));
  }
}




//RAY LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(ray)

list alloc_raylist(){
  list ret = new_list(sizeof(ray));
  return ret;
}

void add_ray(list* l, ray el){
  general_add(l, &el);
}

void rm_ray(list* l, double ind){
  general_rm(l, ind);
}

ray get_ray(list* l, int ind){
  return *((ray*)general_get(l, ind));
}

ray* get_ray_addr(list* l, int ind){
  return ((ray*)general_get(l, ind));
}

void set_ray(list* l, int ind, ray val){
  void* i = malloc(sizeof(ray));
  *((ray*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_ray(list* l, ray val){
  void* v = malloc(sizeof(ray));
  *((ray*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

int cp_rays(void* x1, void* x2, vec3 origin){
  double i1 = ray_dist(*((ray*)x1), origin);
  double i2 = ray_dist(*((ray*)x2), origin);
  return i1 > i2 ? 1 : i1 < i2 ? -1 : 0;
}

void ray_insertion_sort(list* l, int dir, vec3 origin){
  // custom sort
  for(int e1 = 0; e1 < l->num_elements; e1++){
    void* best_val = general_get(l, e1);
    int best_index = e1;
    for(int e2 = e1+1; e2 < l->num_elements; e2++){
      void* c_val = general_get(l, e2);
      best_index = (cp_rays(c_val, best_val, origin) == dir) ? e2 : best_index;
      best_val = (cp_rays(c_val, best_val, origin) == dir) ? c_val : best_val;
    }
    void* f_v = general_get(l, e1);
    void* f_val = malloc(sizeof(l->size_element));
    for(int c = 0; c < l->size_element; c++){
      ((char*)f_val)[c] = ((char*)f_v)[c];
    }
    general_set(l, e1, best_val);
    general_set(l, best_index, f_val);
    free(f_val);
  }
}

void print_ray_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%f\n", get_double(l, e));
  }
}

//MATERIAL LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(material)

list alloc_materiallist(){
  list ret = new_list(sizeof(material));
  return ret;
}

void add_material(list* l, material el){
  // void* i = malloc(sizeof(material));
  general_add(l, (void*)&el);
  // ((material*)l->elements)[l->num_elements-1] = el;
}

void rm_material(list* l, int ind){
  general_rm(l, ind);
}

material get_material(list* l, int ind){
  return *((material*)general_get(l, ind));
}

void set_material(list* l, int ind, material val){
  void* i = malloc(sizeof(material));
  *((material*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_material(list* l, material val){
  void* v = malloc(sizeof(material));
  *((material*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

void print_material_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%f\n", get_material(l, e));
  }
}







//TRIANGLE LIST STRUCTURE
//precondition for all functions:  l->size_element == sizeof(triangle)

list alloc_spherelist(){
  list ret = new_list(sizeof(sphere));
  return ret;
}

void add_sphere(list* l, sphere el){
  general_add(l, &el);
}

void rm_sphere(list* l, int ind){
  general_rm(l, ind);
}

sphere get_sphere(list* l, int ind){
  return *((sphere*)general_get(l, ind));
}

void set_sphere(list* l, int ind, sphere val){
  void* i = malloc(sizeof(sphere));
  *((sphere*)i) = val;
  general_set(l, ind, i);
  free(i);
}

int find_sphere(list* l, sphere val){
  void* v = malloc(sizeof(triangle));
  *((sphere*)v) = val;
  int ret = general_find(l, v);
  free(v);
  return ret;
}

int cp_spheres(void* i1, void* i2){
  return (*((int*)i1) > *((int*)i2)) ? 1 : (*((int*)i1) < *((int*)i2)) ? -1 : 0;
}

void sphere_insertion_sort(list* l, int dir){
  general_insertion_sort(l, cp_ints, -1*dir);
}

void print_sphere_list(list* l){
  for(int e = 0; e < l->num_elements; e++){
    printf("%s\n", "v_a: x:");
    printf("%f", get_triangle(l, e).vertice_a.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_a.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_a.z);
    printf("%s\n", "v_b: x:");
    printf("%f", get_triangle(l, e).vertice_b.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_b.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_b.z);
    printf("%s\n", "v_c: x:");
    printf("%f", get_triangle(l, e).vertice_c.x);
    printf("%s", " y:");
    printf("%f", get_triangle(l, e).vertice_c.y);
    printf("%s", " z:");
    printf("%f", get_triangle(l, e).vertice_c.z);
  }
}
