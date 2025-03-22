#pragma once
#include <stdlib.h>


typedef struct my_integer {
    int value;
} my_integer_t;

my_integer_t* new_int(void* value);

my_integer_t* intSum(my_integer_t* arg1, my_integer_t* arg2);

my_integer_t* intSub(my_integer_t* arg1, my_integer_t* arg2);

my_integer_t* intProduct(my_integer_t* arg1, my_integer_t* arg2);

typedef struct MyDouble {
    double value;
} my_double_t;

my_double_t* new_double(void* value);

my_double_t* doubleSum(my_double_t* arg1, my_double_t* arg2);

my_double_t* doubleSub(my_double_t* arg1, my_double_t* arg2);

my_double_t* doubleProduct(my_double_t* arg1, my_double_t* arg2);

my_double_t* doubleOpposite(my_double_t* arg);

typedef struct MyFloat {
    float value;
} my_float_t;

my_float_t* new_float(void* value);

my_float_t* floatSum(my_float_t* arg1, my_float_t* arg2);

my_float_t* floatSub(my_float_t* arg1, my_float_t* arg2);

my_float_t* floatProduct(my_float_t* arg1, my_float_t* arg2);