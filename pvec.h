//pvec.h
#ifndef PVEC_H
#define PVEC_H

typedef struct /* pvec_t, the Point Vector type */
{
	float x, y;
} pvec_t;

void add_pvec(pvec_t* a, pvec_t* b);
pvec_t add_pvec_new(pvec_t* a, pvec_t* b);
void multiply_pvec(pvec_t* v, float n);
void divide_pvec(pvec_t* v, float n);
void print_pvec(pvec_t* a);
void rotate_pvec(pvec_t* v, float degrees);
float magnitude_pvec(pvec_t* v);
void normalise_pvec(pvec_t* v);
void limit_pvec(pvec_t* v, float limit);

#endif // PVEC_H
