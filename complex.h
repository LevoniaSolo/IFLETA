#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct complex_data 
{
    void* Re;
    void* Im;
} complex_data_t;

typedef void (*set_t) (struct complex*, void*, void*);
typedef void (*del_t) (struct complex*);
typedef struct complex* (*add_t) (struct complex*, struct complex*);
typedef struct complex* (*sub_t) (struct complex*, struct complex*);
typedef struct complex* (*mul_t) (struct complex*, struct complex*);
typedef struct complex* (*opposite_t) (struct complex*);
typedef char* (*toString_t) (struct complex*);
typedef void (*data_alloc_t) (complex_data_t*);
typedef struct complex_vtable {
    del_t del;
    set_t set;
    add_t add;
    sub_t sub;
    mul_t mul;
    opposite_t opposite;
    toString_t toString;
    data_alloc_t data_alloc;
} complex_vtable_t;

typedef struct complex{
    complex_data_t data;
    complex_vtable_t* funcs;
} complex_t;

complex_t* new_complex(complex_vtable_t* funcs);

void set(complex_t* z, void* z1, void* z2);
void setFloat(complex_t* z, void* z1, void* z2);
void setInt(complex_t* z, void* z1, void* z2);

void del(complex_t* z);

char* toString(complex_t* z);
char* toStringFloat(complex_t* z);
char* toStringInt(complex_t* z);

complex_t* add(complex_t* z1, complex_t* z2);
complex_t* addInt(complex_t* z1, complex_t* z2);
complex_t* addFloat(complex_t* z1, complex_t* z2);


complex_t* sub(complex_t* z1, complex_t* z2);

complex_t* mul(complex_t* z1, complex_t* z2);

complex_t* opposite(struct complex* z);
complex_t* oppositeInt(struct complex* z);
complex_t* oppositeFloat(struct complex* z);



void complex_data_alloc(complex_t* data);
void complex_data_alloc_int(complex_data_t* z);
void complex_data_alloc_float(complex_data_t* z);

complex_vtable_t* get_int_vtable();
complex_vtable_t* get_float_vtable();