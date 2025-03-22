#include "vector.h"
#include "fractions.h"

static vector_vtable_t* double_vtable = NULL;
static vector_vtable_t* complex_int_vtable = NULL;
static vector_vtable_t* complex_float_vtable = NULL;

vector_t* new_vector(vector_vtable_t* vFuncs){
    vector_t* v = (vector_t*) malloc(sizeof(vector_t));
    v->vFuncs = vFuncs;
    v->vFuncs->dataV_alloc(&(v->data));
    return v;
}

/////////////////////////////////////////////////////
//setter

void setV(vector_t* v, void* x, void* y, void* z) {
    return v->vFuncs->setV(v, x, y, z);
}

void setVDouble(vector_t* v, void* x, void* y, void* z) {
    memcpy(v->data.x, x, sizeof(double));
    memcpy(v->data.y, y, sizeof(double));
    memcpy(v->data.z, z, sizeof(double));

    
}
void setVComplex(vector_t* v, void* x, void* y, void* z) {
    memcpy(v->data.x, x, sizeof(complex_t));
    memcpy(v->data.y, y, sizeof(complex_t));
    memcpy(v->data.z, z, sizeof(complex_t));
}

void delV(vector_t* v){
    del(v->data.x);
    del(v->data.y);
    del(v->data.z);
    free(v);
}

/////////////////////////////////////////////////////
//выделение памяти

void vector_data_alloc(vector_t* v) {
    if (v == NULL) exit(1);
    v->vFuncs->dataV_alloc(&(v->data));
}

void vector_data_alloc_double(vector_data_t* data) {
    // data->x = malloc(sizeof(double));
    // data->y = malloc(sizeof(double));
    // data->z = malloc(sizeof(double));

    double d = 0.;
    data->x = new_double(&d);
    data->y = new_double(&d);
    data->z = new_double(&d);
}

void vector_data_alloc_complexInt(vector_data_t* data) {
    //data->x = malloc(sizeof(complex_t));
    //data->y = malloc(sizeof(complex_t)); // без этого не работает
    //data->z = malloc(sizeof(complex_t));
    data->x = new_complex(get_int_vtable());
    data->y = new_complex(get_int_vtable());
    data->z = new_complex(get_int_vtable());
}

void vector_data_alloc_complexFloat(vector_data_t* data) {
    // data->x = malloc(sizeof(complex_t));
    // data->y = malloc(sizeof(complex_t));
    // data->z = malloc(sizeof(complex_t));
    data->x = new_complex(get_float_vtable());
    data->y = new_complex(get_float_vtable());
    data->z = new_complex(get_float_vtable());
}

/////////////////////////////////////////////////////
//вывод в строку

char *toVString(vector_t* v) {
    return v->vFuncs->toVString(v);
}

char* toVStringDouble(vector_t* v) {
    char* buff = (char*) malloc(30);
    double* x = (double*) (v->data.x);
    double* y = (double*) (v->data.y);
    double* z = (double*) (v->data.z);

    sprintf(buff, "(%lf; %lf; %lf)", *x, *y, *z);

    return buff;
}
char* toVStringComplex(vector_t* v) {
    char* buff = (char*) malloc(30);
    complex_t* x = (complex_t*) (v->data.x);
    complex_t* y = (complex_t*) (v->data.y);
    complex_t* z = (complex_t*) (v->data.z);
    sprintf(buff, "(%s; %s; %s)", toString(x), toString(y), toString(z));

    return buff;
}

/////////////////////////////////////////////////////
//операции

vector_t* sum(vector_t* v1, vector_t* v2) {
    return v1->vFuncs->sum(v1, v2);
}

vector_t* sumDouble(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_double_vtable());
    my_double_t* x1 = (my_double_t*) (v1->data.x);
    my_double_t* y1 = (my_double_t*) (v1->data.y);
    my_double_t* z1 = (my_double_t*) (v1->data.z);
    my_double_t* x2 = (my_double_t*) (v2->data.x);
    my_double_t* y2 = (my_double_t*) (v2->data.y);
    my_double_t* z2 = (my_double_t*) (v2->data.z);

    buff->data.x = &doubleSum(x1, x2)->value; 
    buff->data.y = &doubleSum(y1, y2)->value;
    buff->data.z = &doubleSum(z1, z2)->value;
    return buff;
}
vector_t* sumComplexInt(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_complex_int_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    buff->data.x = add(x1, x2); 
    buff->data.y = add(y1, y2);
    buff->data.z = add(z1, z2);
    return buff;
}

vector_t* sumComplexFloat(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_complex_float_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    buff->data.x = add(x1, x2); 
    buff->data.y = add(y1, y2);
    buff->data.z = add(z1, z2);
    return buff;
}

char* scalar_product(vector_t* v1, vector_t* v2) {
    return v1->vFuncs->scalar_product(v1, v2);
}

char* scalar_product_double(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    my_double_t* ans;
    my_double_t* x;
    my_double_t* y;
    my_double_t* z;
    my_double_t* x1 = (my_double_t*) (v1->data.x);
    my_double_t* y1 = (my_double_t*) (v1->data.y);
    my_double_t* z1 = (my_double_t*) (v1->data.z);
    my_double_t* x2 = (my_double_t*) (v2->data.x);
    my_double_t* y2 = (my_double_t*) (v2->data.y);
    my_double_t* z2 = (my_double_t*) (v2->data.z);

    x = doubleProduct(x1, x2); 
    y = doubleProduct(y1, y2);
    z = doubleProduct(z1, z2);
    ans = doubleSum(x, y);
    ans = doubleSum(ans, z);
    char* buff = (char*) malloc(30);
    sprintf(buff, "%fl", ans->value);

    return buff;
}
char* scalar_product_complexInt(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* ans = new_complex(get_int_vtable());
    complex_t* x = new_complex(get_int_vtable());
    complex_t* y = new_complex(get_int_vtable());
    complex_t* z = new_complex(get_int_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    x = mul(x1, x2); 
    y = mul(y1, y2);
    z = mul(z1, z2);
    ans = add(x, y);
    ans = add(ans, z);
    char* buff = (char*) malloc(30);
    sprintf(buff, "%s", toString(ans));


    return buff;
}

char* scalar_product_complexFloat(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    complex_t* ans = new_complex(get_float_vtable());
    complex_t* x = new_complex(get_float_vtable());
    complex_t* y = new_complex(get_float_vtable());
    complex_t* z = new_complex(get_float_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    x = mul(x1, x2); 
    y = mul(y1, y2);
    z = mul(z1, z2);
    ans = add(x, y);
    ans = add(ans, z);
    char* buff = (char*) malloc(30);
    sprintf(buff, "%s", toString(ans));

    return buff;
}

vector_t* vector_product(vector_t* v1, vector_t* v2) {
    return v1->vFuncs->vector_product(v1, v2);
}

vector_t* vector_product_double(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_double_vtable());
    my_double_t* x1 = (my_double_t*) (v1->data.x);
    my_double_t* y1 = (my_double_t*) (v1->data.y);
    my_double_t* z1 = (my_double_t*) (v1->data.z);
    my_double_t* x2 = (my_double_t*) (v2->data.x);
    my_double_t* y2 = (my_double_t*) (v2->data.y);
    my_double_t* z2 = (my_double_t*) (v2->data.z);

    buff->data.x = doubleSub(doubleProduct(y1, z2), doubleProduct(z1,y2)); 
    buff->data.y = doubleSub(doubleProduct(z1, x2), doubleProduct(x1,z2));
    buff->data.z = doubleSub(doubleProduct(x1, y2), doubleProduct(y1,x2));

    return buff;
}
vector_t* vector_product_complexInt(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_complex_int_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    buff->data.x = sub(mul(y1, z2), mul(z1,y2)); 
    buff->data.y = sub(mul(z1, x2), mul(x1,z2));
    buff->data.z = sub(mul(x1, y2), mul(y1,x2));

    return buff;
}

vector_t* vector_product_complexFloat(vector_t* v1, vector_t* v2) {
    // if(v1->vFuncs != v2->vFuncs){
    //     printf("Error with wrong typies \n");
    //     exit(1);
    // }
    vector_t* buff = new_vector(get_complex_float_vtable());
    complex_t* x1 = (complex_t*) (v1->data.x);
    complex_t* y1 = (complex_t*) (v1->data.y);
    complex_t* z1 = (complex_t*) (v1->data.z);
    complex_t* x2 = (complex_t*) (v2->data.x);
    complex_t* y2 = (complex_t*) (v2->data.y);
    complex_t* z2 = (complex_t*) (v2->data.z);

    buff->data.x = sub(mul(y1, z2), mul(z1,y2)); 
    buff->data.y = sub(mul(z1, x2), mul(x1,z2));
    buff->data.z = sub(mul(x1, y2), mul(y1,x2));

    return buff;
}



char* mixed_product(struct vector* v1, struct vector* v2, struct vector* v3){
    return scalar_product(vector_product(v1, v2),v3);
}



vector_t* num_product(struct vector* v, void* n){
    return v->vFuncs->num_product(v, n);
}

vector_t* num_product_double(struct vector* v, void* n){
    vector_t* nv = new_vector(get_double_vtable());
    my_double_t* x = (my_double_t*) (v->data.x);
    my_double_t* y = (my_double_t*) (v->data.y);
    my_double_t* z = (my_double_t*) (v->data.z);
    my_double_t* nn = (my_double_t*) (n);

    nv->data.x = doubleProduct(x,nn); 
    nv->data.y = doubleProduct(y,nn);
    nv->data.z = doubleProduct(z,nn);
    return nv;
}

vector_t* num_product_complexInt(struct vector* v, void* n){
    vector_t* nv = new_vector(get_complex_int_vtable());
    complex_t* x = (complex_t*) (v->data.x);
    complex_t* y = (complex_t*) (v->data.y);
    complex_t* z = (complex_t*) (v->data.z);
    complex_t* nn = (complex_t*) (n);

    nv->data.x = mul(x,nn); 
    nv->data.y = mul(y,nn);
    nv->data.z = mul(z,nn);
    return nv;
}

vector_t* num_product_complexFloat(struct vector* v, void* n){
    vector_t* nv = new_vector(get_complex_float_vtable());
    complex_t* x = (complex_t*) (v->data.x);
    complex_t* y = (complex_t*) (v->data.y);
    complex_t* z = (complex_t*) (v->data.z);
    complex_t* nn = (complex_t*) (n);

    nv->data.x = mul(x,nn); 
    nv->data.y = mul(y,nn);
    nv->data.z = mul(z,nn);
    return nv;
}



vector_t* rev(vector_t* v){
    return v->vFuncs->rev(v);
}

vector_t* revDouble(vector_t* v){
    vector_t* nv = new_vector(get_double_vtable());
    my_double_t* x = (my_double_t*) (v->data.x);
    my_double_t* y = (my_double_t*) (v->data.y);
    my_double_t* z = (my_double_t*) (v->data.z);
    nv->data.x = doubleOpposite(x); 
    nv->data.y = doubleOpposite(y);
    nv->data.z = doubleOpposite(z);
    return nv;
}

vector_t* revComplexInt(vector_t* v){
    vector_t* nv = new_vector(get_complex_int_vtable());
    complex_t* x = (complex_t*) (v->data.x);
    complex_t* y = (complex_t*) (v->data.y);
    complex_t* z = (complex_t*) (v->data.z);
    nv->data.x = opposite(x); 
    nv->data.y = opposite(y);
    nv->data.z = opposite(z);
    return nv;
}

vector_t* revComplexFloat(vector_t* v){
    vector_t* nv = new_vector(get_complex_float_vtable());
    complex_t* x = (complex_t*) (v->data.x);
    complex_t* y = (complex_t*) (v->data.y);
    complex_t* z = (complex_t*) (v->data.z);
    nv->data.x = opposite(x); 
    nv->data.y = opposite(y);
    nv->data.z = opposite(z);
    return nv;
}

/////////////////////////////////////////////////////
//getter-ы таблиц

vector_vtable_t* get_double_vtable() {
    if (double_vtable == NULL) {
        double_vtable = (vector_vtable_t*) malloc(sizeof(vector_vtable_t));
        double_vtable->sum = &sumDouble;
        double_vtable->setV = &setVDouble;
        double_vtable->scalar_product = &scalar_product_double;
        double_vtable->vector_product = &vector_product_double;
        double_vtable->num_product = &num_product_double;
        double_vtable->rev = &revDouble;
        double_vtable->toVString = &toVStringDouble;

        double_vtable->dataV_alloc = &vector_data_alloc_double;
    }

    return double_vtable;
}
vector_vtable_t* get_complex_int_vtable() {
    if (complex_int_vtable == NULL) {
        complex_int_vtable = (vector_vtable_t*) malloc(sizeof(vector_vtable_t));
        complex_int_vtable->sum = &sumComplexInt;
        complex_int_vtable->setV = &setVComplex;
        complex_int_vtable->scalar_product = &scalar_product_complexInt;
        complex_int_vtable->vector_product = &vector_product_complexInt;
        complex_int_vtable->num_product = &num_product_complexInt;
        complex_int_vtable->rev = &revComplexInt;
        complex_int_vtable->toVString = &toVStringComplex;

        complex_int_vtable->dataV_alloc = &vector_data_alloc_complexInt;
    }

    return complex_int_vtable;
}
vector_vtable_t* get_complex_float_vtable() {
    if (complex_float_vtable == NULL) {
        complex_float_vtable = (vector_vtable_t*) malloc(sizeof(vector_vtable_t));
        complex_float_vtable->sum = &sumComplexFloat;
        complex_float_vtable->setV = &setVComplex;
        complex_float_vtable->scalar_product = &scalar_product_complexFloat;
        complex_float_vtable->vector_product = &vector_product_complexFloat;
        complex_float_vtable->num_product = &num_product_complexFloat;
        complex_float_vtable->rev = &revComplexFloat;
        complex_float_vtable->toVString = &toVStringComplex;

        complex_float_vtable->dataV_alloc = &vector_data_alloc_complexFloat;
        }

    return complex_float_vtable;
}