#include "pvec.h"
#define VERTS 10

enum sizes {SMALL, MEDIUM, LARGE};

typedef struct
{
	int alive;
	enum sizes size;
	float hit_radius;
	float rotation;
	pvec_t location;
	pvec_t velocity;
	pvec_t obj_vert[VERTS];
	pvec_t world_vert[VERTS];
} ast_t;

void init_asteroids(ast_t asteroids[], int size);
void update_asteroids(ast_t asteroids[], int size);
void draw_asteroids(uint32_t* pixel_buffer, ast_t asteroids[], int size);
int shrink_asteroid(ast_t* a, int size);
void spawn_asteroids(ast_t a[], int length, int size, pvec_t v);
void bounds_asteroids(ast_t asteroids[], int size);
int collision_asteroids(ast_t asteroids[], int size, pvec_t* v, float radius);
