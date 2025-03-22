#include "fractions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

my_integer_t* new_int(void* value){
    my_integer_t* assign = malloc(sizeof(my_integer_t));
    assign->value = *(int*)value;
    return assign;
}

my_integer_t* intSum(my_integer_t* arg1, my_integer_t* arg2){
    my_integer_t* isum = malloc(sizeof(my_integer_t));
    isum->value = arg1->value + arg2->value;
    return isum;
}

my_integer_t* intSub(my_integer_t* a, my_integer_t* b)
{
    my_integer_t* isub = malloc(sizeof(my_integer_t));
    isub->value = a->value - b->value;
    return isub;
}

my_integer_t* intProduct(my_integer_t* arg1, my_integer_t* arg2){
    my_integer_t* iprod = malloc(sizeof(my_integer_t));
    iprod->value = arg1->value * arg2->value;
    return iprod;
}

my_double_t* new_double(void* value){
    my_double_t* assign = malloc(sizeof(my_double_t));
    assign->value = *(double*)value;
    return assign;
}

my_double_t *doubleSum(my_double_t *arg1, my_double_t *arg2)
{
    my_double_t* dsum = malloc(sizeof(my_double_t));
    dsum->value = arg1->value + arg2->value;
    return dsum;
}

my_double_t* doubleSub(my_double_t* a, my_double_t* b){
    my_double_t* dsub = malloc(sizeof(my_double_t));
    dsub->value = a->value - b->value;
    return dsub;
}

my_double_t* doubleProduct(my_double_t* arg1, my_double_t* arg2){
    my_double_t* dprod = malloc(sizeof(my_double_t));
    dprod->value = arg1->value * arg2->value;
    return dprod;
}

my_double_t* doubleOpposite(my_double_t* arg){
    my_double_t* dopp = malloc(sizeof(my_double_t));
    double* m;
    *m = -1;
    my_double_t* Minus = new_double(m);
    dopp->value = arg->value * Minus->value;
    return dopp;
}

my_float_t* new_float(void* value){
    my_float_t* assign = malloc(sizeof(my_float_t));
    assign->value = *(float*)value;
    return assign;
}

my_float_t* floatSum(my_float_t* arg1, my_float_t* arg2){
    my_float_t* fsum = malloc(sizeof(my_float_t));
    fsum->value = arg1->value + arg2->value;
    return fsum;
}

my_float_t* floatSub(my_float_t* a, my_float_t* b){
    my_float_t* fsub = malloc(sizeof(my_float_t));
    fsub->value = a->value - b->value;
    return fsub;
}

my_float_t* floatProduct(my_float_t* arg1, my_float_t* arg2){
    my_float_t* fprod = malloc(sizeof(my_float_t));
    fprod->value = arg1->value * arg2->value;
    return fprod;
}