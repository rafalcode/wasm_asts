//player.c
#include <stdio.h>
#include "renderer.h"
#include "player.h"

void init_player(player_t* p)
{
	pvec_t translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	
	p->hit_radius = 15;
	p->lives = 3;
	p->location.x = 0;
	p->location.y = 0;
	p->velocity.x = 0;
	p->velocity.y = 0;
	p->obj_vert[0].x = 0;
	p->obj_vert[0].y = 1.5;
	p->obj_vert[1].x = -1;
	p->obj_vert[1].y = -1;
	p->obj_vert[2].x = 1;
	p->obj_vert[2].y = -1;

	//convert player verts from object space to world space
	for(int i = 0; i < P_VERTS; i++) {
		multiply_vector(&p->obj_vert[i], -1);
		multiply_vector(&p->obj_vert[i], 12);
        // why not multiply by just -12?

		add_vector(&p->world_vert[i], &p->obj_vert[i]);
		add_vector(&p->world_vert[i], &translation);
	}
	
	for(int i = 0; i < BULLETS; i++)
		p->bullets[i].alive = FALSE;
}

void apply_force(pvec_t* velocity, pvec_t v)
{
	add_vector(velocity, &v);
}

pvec_t get_direction(player_t* p)
{
	pvec_t direction = p->obj_vert[0];
	normalise_vector(&direction);
	return direction;
}

void shoot_bullet(player_t* p)
{
	for(int i = 0; i < BULLETS; i++) {
		if (p->bullets[i].alive == FALSE) {
			p->bullets[i].alive = TRUE;
			p->bullets[i].location = p->world_vert[0];
			p->bullets[i].velocity = get_direction(p);
			multiply_vector(&p->bullets[i].velocity, 4.1);
			break;
		}
	}
}

void draw_player(uint32_t* pixel_buffer, player_t* p)
{
	int i = 0;
	
	if (p->lives > 0) {
		
		draw_line(pixel_buffer, p->world_vert[0].x, p->world_vert[0].y, p->world_vert[1].x, p->world_vert[1].y, 0xffffffff);
		draw_line(pixel_buffer, p->world_vert[1].x, p->world_vert[1].y, p->world_vert[2].x, p->world_vert[2].y, 0xffffffff);
		draw_line(pixel_buffer, p->world_vert[2].x, p->world_vert[2].y, p->world_vert[0].x, p->world_vert[0].y, 0xffffffff);
	}

	/*
	//draw vers representing the player
	for (i = 0; i < P_VERTS; i++) {
	
		draw_pixel(pixel_buffer, p->world_vert[i].x, p->world_vert[i].y, 0xff00ffff);	
	}
	*/

	//draw verts representing the bullets
	for (int i = 0; i < BULLETS; i++) {
		if (p->bullets[i].alive == TRUE)
			draw_pixel(pixel_buffer, p->bullets[i].location.x, p->bullets[i].location.y, 0xffffffff);	
	}

	/*
	//draw vert representing ships location
	pvec_t cpy = {p->location.x, p->location.y};
	pvec_t translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	add_vector(&cpy, &translation);

	draw_pixel(pixel_buffer, cpy.x, cpy.y, 0x00ff00ff);	
	*/
}

void update_player(player_t* p)
{
	limit_vector(&p->velocity, 2);
	add_vector(&p->location, &p->velocity);
	
	pvec_t translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	for(int i =0; i < P_VERTS; i++) {
		p->world_vert[i] = add_vector_new(&p->obj_vert[i], &p->location);	
		add_vector(&p->world_vert[i], &translation);
	}
	
	for(int i = 0; i < BULLETS; i++)
		add_vector(&p->bullets[i].location, &p->bullets[i].velocity);
}

void rotate_player(player_t* p, float degrees)
{
	for(int i =0; i < P_VERTS; i++)
		rotate_vector(&p->obj_vert[i], degrees);
}

void bounds_player(player_t* p)
{
	if (p->location.x < -SCREEN_WIDTH / 2)
		p->location.x = SCREEN_WIDTH / 2;
	
	if (p->location.x > SCREEN_WIDTH / 2)
		p->location.x = -SCREEN_WIDTH / 2;

	if (p->location.y < -SCREEN_HEIGHT / 2)
		p->location.y = SCREEN_HEIGHT / 2;
	
	if (p->location.y > SCREEN_HEIGHT / 2)
		p->location.y = -SCREEN_HEIGHT / 2;

	//bullet is out of bounds, reset bullet to be shot again
	//bullets are in world space
	for(int i = 0; i < BULLETS; i++)
		if (p->bullets[i].location.x < 0 || p->bullets[i].location.x >= SCREEN_WIDTH)
			p->bullets[i].alive = FALSE;
		if (p->bullets[i].location.y < 0 || p->bullets[i].location.y >= SCREEN_HEIGHT)
			p->bullets[i].alive = FALSE;
	}
}
