#include "complex.h"
#include "fractions.h"


static complex_vtable_t* int_vtable = NULL;
static complex_vtable_t* float_vtable = NULL;


complex_t* new_complex(complex_vtable_t* funcs){
    complex_t* z = (complex_t*) malloc(sizeof(complex_t));
    z->funcs = funcs;
    z->funcs->data_alloc(&(z->data));

    return z;
}

/////////////////////////////////////////////////////
//setter

void set(complex_t* z, void* z1, void* z2) {
    return z->funcs->set(z, z1, z2);
}

void setFloat(complex_t* z, void* z1, void* z2) {
    memcpy(z->data.Re, z1, sizeof(float));
    memcpy(z->data.Im, z2, sizeof(float));
}
void setInt(complex_t* z, void* z1, void* z2) {
    memcpy(z->data.Re, z1, sizeof(int));
    memcpy(z->data.Im, z2, sizeof(int));
}

void del(complex_t* z){
    free(z->data.Re);
    free(z->data.Im);
    free(z);
}


/////////////////////////////////////////////////////
//операции суммы, вычетания и умножения add(), sub(), mul()

complex_t* add(complex_t* z1, complex_t* z2){
    return z1->funcs->add(z1, z2);
};

complex_t* addInt(complex_t* z1, complex_t* z2){
    // if(z1->funcs != z2->funcs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* z = new_complex(get_int_vtable());

    my_integer_t* Re1 = new_int(z1->data.Re);
    my_integer_t* Im1 = new_int(z1->data.Im);
    my_integer_t* Re2 = new_int(z2->data.Re);
    my_integer_t* Im2 = new_int(z2->data.Im);
    z->data.Re = intSum(Re1, Re2);
    z->data.Im = intSum(Im1, Im2);
    return z;
};

complex_t* addFloat(complex_t* z1, complex_t* z2){
    // if(z1->funcs != z2->funcs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* z = new_complex(get_float_vtable());
    my_float_t Re1 = *new_float(z1->data.Re);
    my_float_t Im1 = *new_float(z1->data.Im);
    my_float_t Re2 = *new_float(z2->data.Re);
    my_float_t Im2 = *new_float(z2->data.Im);
    z->data.Re = floatSum(&Re1, &Re2);
    z->data.Im = floatSum(&Im1, &Im2);
    return z;
};

complex_t* sub(complex_t* z1, complex_t* z2){
    return z1->funcs->sub(z1, z2);
};

complex_t* subInt(complex_t* z1, complex_t* z2){
    // if(z1->funcs != z2->funcs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* z = new_complex(get_int_vtable());
    my_integer_t* Re1 = new_int(z1->data.Re);
    my_integer_t* Im1 = new_int(z1->data.Im);
    my_integer_t* Re2 = new_int(z2->data.Re);
    my_integer_t* Im2 = new_int(z2->data.Im);
    z->data.Re = intSub(Re1 ,Re2);
    z->data.Im = intSub(Im1, Im2);
    return z;
};

complex_t* subFloat(complex_t* z1, complex_t* z2){
    // if(z1->funcs != z2->funcs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* z = new_complex(get_float_vtable());
    my_float_t* Re1 = new_float(z1->data.Re);
    my_float_t* Im1 = new_float(z1->data.Im);
    my_float_t* Re2 = new_float(z2->data.Re);
    my_float_t* Im2 = new_float(z2->data.Im);
    z->data.Re = floatSub(Re1, Re2);
    z->data.Im = floatSub(Im1, Im2);
    return z;
};

complex_t* mul(complex_t* z1, complex_t* z2){
    return z1->funcs->mul(z1, z2);
};

complex_t* mulInt(complex_t* z1, complex_t* z2){
    // if(z1->funcs != z2->funcs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* z = new_complex(get_int_vtable());
    my_integer_t* Re1 = new_int(z1->data.Re);
    my_integer_t* Im1 = new_int(z1->data.Im);
    my_integer_t* Re2 = new_int(z2->data.Re);
    my_integer_t* Im2 = new_int(z2->data.Im);
    z->data.Re = intSub(intProduct(Re1, Re2), intProduct(Im1, Im2));
    z->data.Im = intSum(intProduct(Im1, Re2), intProduct(Re1, Im2));
    return z;
};

complex_t* mulFloat(complex_t* z1, complex_t* z2){
    if(z1->funcs != z2->funcs){
        printf("Error with wrong typies \n");
        exit(1);
    }
    complex_t* z = new_complex(get_float_vtable());
    my_float_t* Re1 = new_float(z1->data.Re);
    my_float_t* Im1 = new_float(z1->data.Im);
    my_float_t* Re2 = new_float(z2->data.Re);
    my_float_t* Im2 = new_float(z2->data.Im);
    z->data.Re = floatSub(floatProduct(Re1, Re2), floatProduct(Im1, Im2));
    z->data.Im = floatSum(floatProduct(Im1, Re2), floatProduct(Re1, Im2));
    return z;
};

complex_t* opposite(complex_t* z){
    return z->funcs->opposite(z);
}

complex_t* oppositeInt(complex_t* z){
    complex_t* nz = new_complex(get_int_vtable());
    my_integer_t* Re = new_int(z->data.Re);
    my_integer_t* Im = new_int(z->data.Im);
    int* m;
    *m = -1;
    my_integer_t* Minus = new_int(m);
    nz->data.Re = intProduct(Re, Minus);
    nz->data.Im = intProduct(Im, Minus);
    return nz;
}

complex_t* oppositeFloat(complex_t* z){
    complex_t* nz = new_complex(get_float_vtable());
    my_float_t* Re = new_float(z->data.Re);
    my_float_t* Im = new_float(z->data.Im);
    float* m;
    *m = -1;
    my_float_t* Minus = new_float(m);
    nz->data.Re = floatProduct(Re, Minus);
    nz->data.Im = floatProduct(Im, Minus);
    return nz;
}


/////////////////////////////////////////////////////
//вывод в строку

char *toString(complex_t* z) {
    return z->funcs->toString(z);
}

char* toStringFloat(complex_t* z) {
    char* buff = (char*) malloc(30);
    my_float_t* Re = new_float(z->data.Re);
    my_float_t* Im = new_float(z->data.Im);
    sprintf(buff, "(%f + %fi)", Re->value, Im->value);

    return buff;
}
char* toStringInt(complex_t* z) {
    char* buff = (char*) malloc(30);
    my_integer_t* Re = new_int(z->data.Re);
    my_integer_t* Im = new_int(z->data.Im);
    sprintf(buff, "(%d + %di)", (Re->value), Im->value);

    return buff;
}

/////////////////////////////////////////////////////
//выделение памяти


void complex_data_alloc(complex_t* z) {
    if (z == NULL) exit(1);
    z->funcs->data_alloc(&(z->data));
}

void complex_data_alloc_int(complex_data_t* data) {
    data->Re = malloc(sizeof(int));
    data->Im = malloc(sizeof(int));

    int i = 0;
    *(int*)(data->Re) = new_int(&i)->value;
    *(int*)(data->Im) = new_int(&i)->value;
}

void complex_data_alloc_float(complex_data_t* data) {
    data->Re = malloc(sizeof(float));
    data->Im = malloc(sizeof(float));

    float f = 0.;
    *(float*)(data->Re) = new_float(&f)->value;
    *(float*)(data->Im) = new_float(&f)->value;
}

/////////////////////////////////////////////////////
//getter-ы таблиц

complex_vtable_t* get_int_vtable() {
    if (int_vtable == NULL) {
        int_vtable = (complex_vtable_t*) malloc(sizeof(complex_vtable_t));
        int_vtable->set = &setInt;
        int_vtable->add = &addInt;
        int_vtable->sub = &subInt;
        int_vtable->mul = &mulInt;
        int_vtable->opposite = &oppositeInt;
        int_vtable->toString = &toStringInt;
        int_vtable->data_alloc = &complex_data_alloc_int;
    }

    return int_vtable;
}
complex_vtable_t* get_float_vtable() {
    if (float_vtable == NULL) {
        float_vtable = (complex_vtable_t*) malloc(sizeof(complex_vtable_t));
        float_vtable->set = &setFloat;
        float_vtable->add = &addFloat;
        float_vtable->sub = &subFloat;
        float_vtable->mul = &mulFloat;
        float_vtable->opposite = &oppositeFloat;
        float_vtable->toString = &toStringFloat;
        float_vtable->data_alloc = &complex_data_alloc_float;
    }

    return float_vtable;
}