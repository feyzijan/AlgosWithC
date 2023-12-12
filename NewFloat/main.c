#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

int main (int argc, char *argv[]){


    // Read Command Line Arguements

    if (argc < 4){
        printf("Error: Not enough arguements");
        return 1;
    } else if (argc > 6){
        printf("Error: Too many arguements");
        return 1;
    }

    // 1. Total Number of Bits - Must be between 8 and 64
    int n_total_bits = atoi(argv[1]); 
    if (n_total_bits < 8){
        printf("Error: Total Number of Bits must be greater than 8");
        //return 1;
        n_total_bits = 8;
    } else if (n_total_bits > 64){
        printf("Error: Total Number of Bits must be less than 64");
        //return 1;
        n_total_bits = 64;
    }

    // 2. Number of Mantissa Bits - Must be between 1 and n_total_bits - 2
    int n_mantissa_bits = atoi(argv[2]);
    if (n_mantissa_bits < 1){
        printf("Error: Number of Mantissa Bits must be at least 1");
        //return 1;
        n_mantissa_bits = 1;
    } else if (n_mantissa_bits > n_total_bits - 2){
        printf("Error: Number of Mantissa Bits must be less than Total Number of Bits - 2");
        //return 1;
        n_mantissa_bits = n_total_bits - 2;
    }

    
    // Now on to the floating point stuff
    int n_exponent_bits = n_total_bits - n_mantissa_bits - 1;
    int exponent_bias = (1 << (n_exponent_bits - 1)) - 1; // shift 1 by n - 1 to take power of 2


    // 3. Operation to perform name
    char *operation = argv[3];

    // Operation 1 - convert number
    if (strcmp(operation, "convert") == 0){
        // printf("Converting Number\n");
        char * bitstring = argv[4];

        // Get number
        double final_number = BinaryToFloat(bitstring, n_mantissa_bits, n_exponent_bits);

        printf("%f", final_number);
    }  
    
    // Operation 2 - Calculate Min and Max
    else if (strcmp(operation, "minmax") == 0){
        CalculateMinMax(n_mantissa_bits, n_exponent_bits);
    }

    // Operation 3 - Add the two hex numbers
    else if (strcmp(operation,"addhex") == 0){

        char * hex_1 = argv[4];
        char * hex_2 = argv[5];
        AddHex(hex_1, hex_2, n_total_bits, n_mantissa_bits, n_exponent_bits);
     
    } else {
        printf("Error: Operation not recognized");
        return -1;
    }


   return 0; 
}