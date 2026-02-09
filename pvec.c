#include <stdio.h>
#include <math.h>
#include "pvec.h"

void add_pvec(pvec_t* a, pvec_t* b)
{
	a->x += b->x;
	a->y += b->y;
}

pvec_t add_pvec_new(pvec_t* a, pvec_t* b)
{
	pvec_t new = {a->x + b->x, a->y + b->y};
	return new;
}

void multiply_pvec(pvec_t* v, float n)
{
	v->x *= n;
	v->y *= n;
}

void divide_pvec(pvec_t* v, float n)
{
	v->x /= n;
	v->y /= n;
}

void print_pvec(pvec_t* a)
{
	printf("x = %f\n y = %f\n", a->x, a->y);
}

float magnitude_pvec(pvec_t* v)
{
	float c2 = pow(v->x, 2) + pow(v->y, 2); 
	return sqrt(c2);
}

void normalise_pvec(pvec_t* v)
{
	float mag = magnitude_pvec(v);
	divide_pvec(v, mag);
}

void limit_pvec(pvec_t* v, float limit)
{
    float ratio;
	float mag = magnitude_pvec(v);
	if (mag > limit) {
		ratio = limit / mag;
		v->x *= ratio;
		v->y *= ratio;
	}
}

void rotate_pvec(pvec_t* v, float degrees)
{
	//calculate radians
	float angle = degrees * M_PI / 180;
	float sine = sin(angle);
	float cosine = cos(angle);
	
	//rotation matix
	float matrix[2][2] = {{cosine, -sine}, {sine, cosine}};

	v->x = matrix[0][0] * v->x + matrix[0][1] * v->y;
    v->y = matrix[1][0] * v->x + matrix[1][1] * v->y;
}

