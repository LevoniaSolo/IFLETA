#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "fractions.h"
#include "vector.h"
#include <string.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void wrout(char* message) {
    FILE* outputF = fopen(OUTPUT_FILE, "a");
    if (outputF) {
        fprintf(outputF, "%s\n", message);
        fclose(outputF);
    }
}

int main() {
    FILE* inputF = fopen(INPUT_FILE, "r");
    if (!inputF) {
        wrout("Error: Cannot open input file.");
        return 1;
    }
    
    FILE* outputF = fopen(OUTPUT_FILE, "w");
    if (!outputF) {
        fclose(inputF);
        wrout("Error: Cannot open output file.");
        return 1;
    }
    fclose(outputF);
    
    char command[50];
    vector_vtable_t* type1;
    vector_t* v1 = NULL;
    vector_vtable_t* type2;
    vector_t* v2 = NULL;
    
    while (fscanf(inputF, "%s", command) != EOF) {
        if (strcmp(command, "NEW1") == 0) {
            char typeStr[10];
            fscanf(inputF, "%s", typeStr);
            if (strcmp(typeStr, "DOUBLE") == 0) type1 = get_double_vtable();
            else if (strcmp(typeStr, "COMPLEX_INT") == 0) type1 = get_complex_int_vtable();
            else if (strcmp(typeStr, "COMPLEX_FLOAT") == 0) type1 = get_complex_float_vtable();
            else {
                wrout("Error: Invalid data type.");
                continue;
            }
            v1 = new_vector(type1);
            wrout("Vector 1 created.");
            // wrout(toVString(v1));
        }
        else if (strcmp(command, "NEW2") == 0) {
            char typeStr[10];
            fscanf(inputF, "%s", typeStr);
            if (strcmp(typeStr, "DOUBLE") == 0) type2 = get_double_vtable();
            else if (strcmp(typeStr, "COMPLEX_INT") == 0) type2 = get_complex_int_vtable();
            else if (strcmp(typeStr, "COMPLEX_FLOAT") == 0) type2 = get_complex_float_vtable();
            else {
                wrout("Error: Invalid data type.");
                continue;
            }
            v2 = new_vector(type2);
            wrout("Vector 2 created.");
            // wrout(toVString(v2));
        }
        else if (strcmp(command, "SET1") == 0) {
            if (!v1) {
                wrout("Error: Vector 1 not created.");
                continue;
            }
            
            char typeStr[10];
            fscanf(inputF, "%s", typeStr);
            vector_vtable_t* inputType;
            if (strcmp(typeStr, "DOUBLE") == 0) inputType = get_double_vtable();
            else if (strcmp(typeStr, "COMPLEX_INT") == 0) inputType = get_complex_int_vtable();
            else if (strcmp(typeStr, "COMPLEX_FLOAT") == 0) inputType = get_complex_float_vtable();
            else {
                wrout("Error: Invalid data type.");
                continue;
            }
            
            if (inputType != v1->vFuncs) {
                wrout("Error: Wrong data type for Vector 1.");
                continue;
            }
            
            if (v1->vFuncs == get_double_vtable()) {
                double x, y, z;
                fscanf(inputF, "%lf", &x);
                fscanf(inputF, "%lf", &y);
                fscanf(inputF, "%lf", &z);
                setV(v1, &x, &y, &z);
            } else if (v1->vFuncs == get_complex_int_vtable()) {
                complex_t* x = new_complex(get_int_vtable());
                int rx,ix;
                fscanf(inputF, "%d", &rx);
                fscanf(inputF, "%d", &ix);
                set(x, &rx, &ix);
                complex_t* y = new_complex(get_int_vtable());
                int ry,iy;
                fscanf(inputF, "%d", &ry);
                fscanf(inputF, "%d", &iy);
                set(y, &ry, &iy);
                complex_t* z = new_complex(get_int_vtable());
                int rz,iz;
                fscanf(inputF, "%d", &rz);
                fscanf(inputF, "%d", &iz);
                set(z, &rz, &iz);
                setV(v1, x, y, z);
            } else if (v1->vFuncs == get_complex_float_vtable()) {
                complex_t* x = new_complex(get_float_vtable());
                float rx,ix;
                fscanf(inputF, "%f", &rx);
                fscanf(inputF, "%f", &ix);
                set(x, &rx, &ix);
                complex_t* y = new_complex(get_float_vtable());
                float ry,iy;
                fscanf(inputF, "%f", &ry);
                fscanf(inputF, "%f", &iy);
                set(y, &ry, &iy);
                complex_t* z = new_complex(get_float_vtable());
                float rz,iz;
                fscanf(inputF, "%f", &rz);
                fscanf(inputF, "%f", &iz);
                set(z, &rz, &iz);
                setV(v1, x, y, z);
            }
            wrout("Elements set to Vector 1.");
        }
        else if (strcmp(command, "SET2") == 0) {
            if (!v2) {
                wrout("Error: Vector 2 not created.");
                continue;
            }
            
            char typeStr[10];
            fscanf(inputF, "%s", typeStr);
            vector_vtable_t* inputType;
            if (strcmp(typeStr, "DOUBLE") == 0) inputType = get_double_vtable();
            else if (strcmp(typeStr, "COMPLEX_INT") == 0) inputType = get_complex_int_vtable();
            else if (strcmp(typeStr, "COMPLEX_FLOAT") == 0) inputType = get_complex_float_vtable();
            else {
                wrout("Error: Invalid data type.");
                continue;
            }
            
            if (inputType != v2->vFuncs) {
                wrout("Error: Wrong data type for Vector 2.");
                continue;
            }
            
            if (v2->vFuncs == get_double_vtable()) {
                double x, y, z;
                fscanf(inputF, "%lf", &x);
                fscanf(inputF, "%lf", &y);
                fscanf(inputF, "%lf", &z);
                setV(v2, &x, &y, &z);
            } else if (v2->vFuncs == get_complex_int_vtable()) {
                complex_t* x = new_complex(get_int_vtable());
                int rx,ix;
                fscanf(inputF, "%d", &rx);
                fscanf(inputF, "%d", &ix);
                set(x, &rx, &ix);
                complex_t* y = new_complex(get_int_vtable());
                int ry,iy;
                fscanf(inputF, "%d", &ry);
                fscanf(inputF, "%d", &iy);
                set(y, &ry, &iy);
                complex_t* z = new_complex(get_int_vtable());
                int rz,iz;
                fscanf(inputF, "%d", &rz);
                fscanf(inputF, "%d", &iz);
                set(z, &rz, &iz);
                setV(v2, x, y, z);
            } else if (v2->vFuncs == get_complex_float_vtable()) {
                complex_t* x = new_complex(get_float_vtable());
                float rx,ix;
                fscanf(inputF, "%f", &rx);
                fscanf(inputF, "%f", &ix);
                set(x, &rx, &ix);
                complex_t* y = new_complex(get_float_vtable());
                float ry,iy;
                fscanf(inputF, "%f", &ry);
                fscanf(inputF, "%f", &iy);
                set(y, &ry, &iy);
                complex_t* z = new_complex(get_float_vtable());
                float rz,iz;
                fscanf(inputF, "%f", &rz);
                fscanf(inputF, "%f", &iz);
                set(z, &rz, &iz);
                setV(v2, x, y, z);
            }
            wrout("Elements set to Vector 2.");
        } 
        else if (strcmp(command, "SUM_VECTORS") == 0) {
            if (!v1 || !v2) {
                wrout("Error: One or both vectors not created.");
                continue;
            }
            
            if (v1->vFuncs != v2->vFuncs) {
                wrout("Error: Cannot add vectors of different types.");
                continue;
            }
            
            vector_t* result = sum(v1, v2);
            if (result) {
                wrout("Vectors added successfully.");
                wrout(toVString(result));
                del(result);
            } else {
                wrout("Error: Vector addition failed.");
            }
        } 
        else if (strcmp(command, "DELETE") == 0) {
            if (v1) {
                del(v1);
                v1 = NULL;
                wrout("Vector 1 deleted.");
            }
            if (v2) {
                del(v2);
                v2 = NULL;
                wrout("Vector 2 deleted.");
            }
        } 
        else if (strcmp(command, "SCALAR_PRODUCT") == 0) {

            if (!v1 || !v2) {
                wrout("Error: One or both vectors not created.");
                continue;
            }
            if (v1->vFuncs != v2->vFuncs) {
                wrout("Error: Cannot make scalar product of different types.");
                continue;
            }
            // if (v1->vFuncs == get_double_vtable()) {
            //     double result;
            //     result = *(double*)scalar_product(v1, v2);
            //     char sres[30];
            //     sprintf(sres, "%lf", result);
            //     wrout("Scalar product was made successfully.");
            //     wrout(sres);
            // }
            // else if (v1->vFuncs == get_complex_int_vtable()) {
            //     complex_t* result = new_complex(get_complex_int_vtable());
            //     result = scalar_product(v1, v2);
            //     char sres[30];
            //     sprintf(sres, "%s", toString(result));
            //     wrout("Scalar product was made successfully.");
            //     wrout(sres);
            // }
            // else if (v1->vFuncs == get_complex_float_vtable()) {
            //     complex_t* result = new_complex(get_complex_float_vtable());
            //     result = scalar_product(v1, v2);
            //     char sres[30];
            //     sprintf(sres, "%s", toString(result));
            //     wrout("Scalar product was made successfully.");
            //     wrout(sres);
            // }
            char* result = (char*) malloc(30);
            result = scalar_product(v1,v2);
            wrout("Scalar product was made successfully.");
            wrout(result);

        } 
        else if (strcmp(command, "VECTOR_PRODUCT") == 0) {
            if (!v1 || !v2) {
                wrout("Error: One or both vectors not created.");
                continue;
            }
            if (v1->vFuncs != v2->vFuncs) {
                wrout("Error: Cannot make vector product of different types.");
                continue;
            }
            vector_t* result = vector_product(v1, v2);
            if (result) {
                wrout("Vector product was made successfully.");
                wrout(toVString(result));
                del(result);
            } else {
                wrout("Error: Vector product compilation failed.");
            }
        } else {
            wrout("Error: Unknown command.");
        }
    }
    
    
    if (v1) {
        del(v1);
    }
    if (v2) {
        del(v2);
    }
    fclose(inputF);








    // complex_t* z1 = new_complex(get_int_vtable());
    // complex_t* z2 = new_complex(get_int_vtable());
    // complex_t* z3 = new_complex(get_int_vtable());
    // // complex_t* z4 = new_complex(get_int_vtable());
    // // complex_t* z5 = new_complex(get_int_vtable());

    // int a, b, c, d, e, f, g, h;
    // a = 1;
    // b = 2;
    // c = 3;
    // // d = 8;
    // // e = 9;
    // set(z1, &a, &b);
    // set(z2, &c, &a);

    // z3 = add(z1, z2);
    // // complex_t* z0 = new_complex(get_float_vtable());


    // // float f1;
    // // float f2;
    // // f1 = 4;
    // // f2 = 5;
    // // set(z0, &f1, &f2);

    // // // mul(z3, z0);
    // // // del(z0);

    // // printf("%s\n", toString(opposite(z2)));


    // double d1, d2, d3, d4;
    // d1 = 1;
    // d2 = 2;
    // d3 = 3;
    // // double* d5;

    // vector_t* v01 = new_vector(get_double_vtable());
    // vector_t* v02 = new_vector(get_double_vtable());
    // vector_t* v03 = new_vector(get_double_vtable());

    // setV(v01, &d1, &d2, &d3);
    // setV(v02, &d2, &d3, &d1);

    // printf("%s\n", toVString(num_product(v01, &d2)));


    // // // del(v1);
    // // // printf("%s\n", toVString(v1));

    // // v03 = sum(v01, v02);
    // setV(v03, &d3, &d1, &d3);
    // printf("%s\n", mixed_product(v01, v02, v03));
    // // // d4 = *(double*)scalar_product(v1, v2);
    // // // v3 = vector_product(v1, v2);

    // // // printf("%fl\n", d4);

    // // // printf("%s\n", toVString(v3));


    // vector_t* v111 = new_vector(get_complex_int_vtable());
    // vector_t* v112 = new_vector(get_complex_int_vtable());
    // vector_t* v113 = new_vector(get_complex_int_vtable());

    // setV(v111, z1, z2, z3);
    // setV(v112, z2, z3, z1);
    // // printf("%s\n", toString(opposite(z1)));

    // printf("%s\n", toVString(v111));
    // printf("%s\n", toVString(num_product(v111, z1)));




    // // v113 = sum(v111, v112);
    // setV(v113, z3, z2, z1);

    // // // v113 = scalar_product(v111, v112);
    // // // v113 = vector_product(v111, v112);
    // printf("%s\n", toVString(rev(v113)));
    // printf("%s\n", mixed_product(v111, v112, v113));


    // // // printf("%s\n", toVString(v111));

    // // vector_t* v121 = new_vector(get_complex_float_vtable());
    // // vector_t* v122 = new_vector(get_complex_float_vtable());
    // // vector_t* v123 = new_vector(get_complex_float_vtable());
    // // v123 = sum(v121, v122);
    // // // v113 = scalar_product(v121, v122);
    // // v123 = vector_product(v121, v122);
    // // // printf("%s\n", toVString(v123));
    // // // printf("%s\n", toVString(v121));
    return EXIT_SUCCESS;
}