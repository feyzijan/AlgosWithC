#include <stdio.h>
#include <math.h>


struct val_and_index
{
    double max_val;
    int max_val_index;
};


void method_1(double* array, double* max_val, int* max_val_index) {

    *max_val = 0; // initial value
    // find max val and index by looping
    for (int i = 0; i<100; i++) {
        if (array[i] > *max_val) {
            *max_val = array[i];
            *max_val_index = i;
        }
    }

}


double method_2(double* array, int* max_val_index) {

    double local_max_val = 0;
    // find max val and index by looping
    for (int i = 0; i<100; i++) {
        if (array[i] > local_max_val) {
            local_max_val = array[i];
            *max_val_index = i;
        }
    }
    return local_max_val;

}


struct val_and_index method_3(double* array) {

    struct val_and_index result_struct;
    result_struct.max_val = 0;

    // find max val and index by looping
    for (int i = 0; i<100; i++) {
        if (array[i] > result_struct.max_val) {
            result_struct.max_val = array[i];
            result_struct.max_val_index = i;
        }
    }

    return result_struct;

}


int main() {

    double my_array[100];
    //printf("aaa");

    for (int i = 0; i<100; i++) {
        my_array[i] = 1 + sin(i);
        //printf("%f\n", my_array[i]);
    }
    //printf("Array created");

    double max_val = 0.0;
    int max_val_index = 0;

    printf("\nMethod 1\n");
    printf("Initially: Max val: %f Max val index: %d \n", max_val, max_val_index);
    method_1(my_array, &max_val, &max_val_index);
    printf("After: Max val: %f Max val index: %d\n", max_val, max_val_index);

    // reset to zero
    max_val = 0;
    max_val_index = 0;
    printf("\nMethod 2\n");
    printf("Initially: Max val: %f Max val index: %d\n", max_val, max_val_index);
    max_val = method_2(my_array, &max_val_index);
    printf("After: Max val: %f Max val index: %d\n", max_val, max_val_index);


    printf("\nMethod 3\n");
    struct val_and_index result_struct;
    printf("Initially: Max val: %f Max val index: %d\n", result_struct.max_val, result_struct.max_val_index);
    result_struct = method_3(my_array);
    printf("After: Max val: %f Max val index: %d \n", result_struct.max_val, result_struct.max_val_index);

    return 0;
}





