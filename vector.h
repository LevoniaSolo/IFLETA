#pragma once
#include <stdlib.h>
#include "complex.h"

typedef struct vector_data{
    void *x;
    void *y;
    void *z;
} vector_data_t;

typedef void (*dataV_alloc_t) (vector_data_t*);
typedef char* (*toVString_t) (struct vector*);
typedef void (*setV_t) (struct vector*, void*, void*, void*);
typedef void (*delV_t) (struct vector*);

typedef struct vector* (*sum_t) (struct vector*, struct vector*);
typedef char* (*scalar_product_t) (struct vector*, struct vector*);
typedef struct vector* (*vector_product_t) (struct vector*, struct vector*);
typedef char* (*mixed_product_t) (struct vector*, struct vector*, struct vector*);
typedef struct vector* (*num_product_t) (struct vector*, void*);
typedef struct vector* (*rev_t) (struct vector*);


typedef struct vector_vtable {
    delV_t delV;
    dataV_alloc_t dataV_alloc;
    toVString_t toVString;
    setV_t setV;
    sum_t sum;
    scalar_product_t scalar_product;
    vector_product_t vector_product;
    mixed_product_t mixed_vector;
    num_product_t num_product;
    rev_t rev;
} vector_vtable_t;


typedef struct vector
{
    // int flag;
    vector_data_t data;
    vector_vtable_t* vFuncs;
} vector_t;

char* toVString(vector_t* v);
char* toVStringDouble(vector_t* v);
char* toVStringComplex(vector_t* v);

void delV(vector_t* v);

void setV(vector_t* v, void* x, void* y, void* z);
void setVDouble(vector_t* v, void* x, void* y, void* z);
void setVComplexInt(vector_t* v, void* x, void* y, void* z);
void setVComplexFloat(vector_t* v, void* x, void* y, void* z); // допилить сеттеры 


vector_t* sum(vector_t* v1, vector_t* v2);
vector_t* sumDouble(vector_t* v1, vector_t* v2);
vector_t* sumComplexInt(vector_t* v1, vector_t* v2);
vector_t* sumComplexFloat(vector_t* v1, vector_t* v2);

vector_t* new_vector(vector_vtable_t* vFuncs);

void complex_data_alloc(complex_t* data);
void complex_data_alloc_int(complex_data_t* v);
void complex_data_alloc_float(complex_data_t* v);

char* scalar_product(struct vector* v1, struct vector* v2);
char* scalar_product_double(struct vector* v1, struct vector* v2);
char* scalar_product_complexInt(struct vector* v1, struct vector* v2);
char* scalar_product_complexFloat(struct vector* v1, struct vector* v2);

vector_t* vector_product(struct vector*, struct vector*);
vector_t* vector_product_double(struct vector*, struct vector*);
vector_t* vector_product_complexInt(struct vector*, struct vector*);
vector_t* vector_product_complexFloat(struct vector*, struct vector*);

char* mixed_product(struct vector* v1, struct vector* v2, struct vector* v3);

vector_t* num_product(struct vector* v, void* n);
vector_t* num_product_double(struct vector* v, void* n);
vector_t* num_product_complexInt(struct vector* v, void* n);
vector_t* num_product_complexFloat(struct vector* v, void* n);

vector_t* rev(struct vector* v);
vector_t* revDouble(struct vector* v);
vector_t* revComplexInt(struct vector* v);
vector_t* revComplexFloat(struct vector* v);




vector_vtable_t* get_double_vtable();
vector_vtable_t* get_complex_int_vtable();
vector_vtable_t* get_complex_float_vtable();

