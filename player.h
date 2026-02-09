//player.h
#include "pvec.h"

#define P_VERTS 3 // three vertices for the player's ship (a triangle)
#define BULLETS 3
	
enum boolean {TRUE, FALSE};

typedef struct
{
	pvec_t location;
	pvec_t velocity;
	enum boolean alive;
} bullet_t;

typedef struct
{
	float hit_radius;
	int lives;
	pvec_t location;
	pvec_t velocity;
	pvec_t obj_vert[P_VERTS];
	pvec_t world_vert[P_VERTS];
	bullet_t bullets[BULLETS];
} player_t;

void init_player(player_t* p);
void draw_player(uint32_t* pixel_buffer, player_t* p);
void shoot_bullet(player_t* p);
void update_player(player_t* p);
void bounds_player(player_t* p);
void apply_force(pvec_t* velocity, pvec_t v);
void rotate_player(player_t* p, float degrees);
pvec_t get_direction(player_t* p);
