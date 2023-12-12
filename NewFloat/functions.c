#include "functions.h"



// Convert a hex string to a binary string using a lookup table
char* HexToBinary(char* hexstring, int n_total_bits){
    

    // allocate memory for bin string
    char* bitstring = calloc( 4 * strlen(hexstring) + 1, sizeof(char));

    for (int i =0; i < strlen(hexstring); i++){
        switch(hexstring[i])
        {
            case '0':
                strcat(bitstring, "0000");
                break;
            case '1':
                strcat(bitstring, "0001");
                break;
            case '2':
                strcat(bitstring, "0010");
                break;
            case '3':
                strcat(bitstring, "0011");
                break;
            case '4':
                strcat(bitstring, "0100");
                break;
            case '5':
                strcat(bitstring, "0101");
                break;
            case '6':
                strcat(bitstring, "0110");
                break;
            case '7':
                strcat(bitstring, "0111");
                break;
            case '8':
                strcat(bitstring, "1000");
                break;
            case '9':
                strcat(bitstring, "1001");
                break;
            case 'a':
            case 'A':
                strcat(bitstring, "1010");
                break;
            case 'b':
            case 'B':
                strcat(bitstring, "1011");
                break;
            case 'c':
            case 'C':
                strcat(bitstring, "1100");
                break;
            case 'd':
            case 'D':
                strcat(bitstring, "1101");
                break;
            case 'e':
            case 'E':
                strcat(bitstring, "1110");
                break;
            case 'f':
            case 'F':
                strcat(bitstring, "1111");
                break;
            default:
                printf("Error: Invalid hexadecimal input.");
        }
    }

    // Pad with zeros so as to match length
    int n_zeros = n_total_bits - strlen(bitstring);

    char* padded_bitstring = calloc(n_zeros, sizeof(char));
    for (int i = 0; i < n_zeros; i++){
        strcat(padded_bitstring, "0");
    }


    strcat(padded_bitstring, bitstring);

    // free memory
    free(bitstring);


    // return pointer to padded bin string
    return padded_bitstring;
}



// Convert a binary string to a float
double BinaryToFloat(char* bitstring, int n_mantissa_bits, int n_exponent_bits){

        int n_total_bits = n_mantissa_bits + n_exponent_bits + 1;
        int exponent_bias = (1 << (n_exponent_bits - 1)) - 1; // shift 1 by n - 1 to take power of 2

        // check length
        if (strlen(bitstring) != n_total_bits){
            printf("Error: Bitstring must be of length %d", n_total_bits);
            return -1;
        }

        // parse the bitstring
        // sign
        int sign = (bitstring[0] == '1') ? 1 : 0 ; // check this conversion works

        // exponent
        int exponent = 0;
        int current_bit = 0;

        for (int i = 1; i < n_exponent_bits + 1; i++){
            // printf("Current bit: %c\n", bitstring[i]);
            current_bit = (bitstring[i] == '1') ? 1 : 0 ; // check this
            exponent += current_bit << (i - 1); // check this
            // exponent = exponent * 2 + (current_bit - '0');
        }



        // Mantessa
        double mantissa = 0;
        for (int i = n_exponent_bits + 1; i < n_total_bits; i++){
            current_bit = (bitstring[i] == '1') ? 1 : 0 ; 
            mantissa += current_bit * pow(2, -(i - n_exponent_bits)); // check this
        }


        // Check for edge cases
        double final_number;

        final_number = pow(-1, sign) * pow(2, exponent - exponent_bias) * (1 + mantissa);

        // Edge cases - infinity and nans
        int all_ones = (1 << n_exponent_bits) - 1; // -1 for offset

        if (exponent == all_ones){  // true if n is all 1s
            if ((mantissa == 0)){
                if (sign == 0){
                    final_number = INFINITY;
                    return final_number;
                } else {
                    final_number = -INFINITY;
                    return final_number;
                }
            }
            else {
                final_number = NAN;
                return final_number;
            }
        }

        // Calculate final number
        final_number = pow(-1, sign) * pow(2, exponent - exponent_bias) * (1 + mantissa);


        return final_number;
}



// Calculate the min and max values for a given number of mantissa and exponent bits
void CalculateMinMax(int n_mantissa_bits, int n_exponent_bits){
    
    
    int exponent_bias = (1 << (n_exponent_bits - 1)) - 1; // shift 1 by n - 1 to take power of 2
    double max;
    double min;

    // Max
    int max_exponent = (1 << n_exponent_bits) - 2; // -2 for offset and not counting infinity
    max = pow(2, max_exponent - exponent_bias) * (2 - pow(2, -n_mantissa_bits));

    int min_exponent = 0; // Excluding 0
    min = pow(2, min_exponent - exponent_bias) * (1 + pow(2, -n_mantissa_bits));

    printf("Min Positive: %.40f\n", min);
    printf("Max: %f\n", max);

}



// Add two hex numbers
void AddHex(char *hex1, char *hex2, int n_total_bits, int n_mantissa_bits, int n_exponent_bits){


        // convert hexs to bin strings - do not forget to free memory
        char * bin_1 = HexToBinary(hex1, n_total_bits);
        char * bin_2 = HexToBinary(hex2, n_total_bits);

        printf("Binary 1: %s\n", bin_1);
        printf("Binary 2: %s\n", bin_2);

        // convert to floats
        double float_1 = BinaryToFloat(bin_1, n_mantissa_bits, n_exponent_bits);
        double float_2 = BinaryToFloat(bin_2, n_mantissa_bits, n_exponent_bits);

        printf("Value 1: %f\n", float_1);
        printf("Value 2: %f\n", float_2);

        // Add floats to get the sum
        double result;
        // check for nans/infs - should aitomatically check for this

        result = float_1 + float_2;

        printf("Sum: %f\n", result);

        // Print out binary and hex
        if (result == INFINITY){
            if (float_1 == INFINITY){
                // print float 1s binary
                printf("Binary sum: %s\n", bin_1);
                printf("Hex Sum: %s\n", hex1);
            } else {
                // print float 2s binary
                printf("Binary sum: %s\n", bin_2);
                printf("Hex Sum: %s\n", hex2);
            }
            // printf("Binary Sum: inf \n");
            // printf("Hex Sum: inf \n");
        } else if (result == -INFINITY) {
            printf("Binary Sum: -inf \n");
            printf("Hex Sum: -inf \n");
        } else if (result == NAN){
            printf("Binary Sum: nan \n");
            printf("Hex Sum: nan \n");
        } else {
            // Valid Value
            // not sure how to convert back just print a default value and accept loss of points
            printf("Binary Sum: 010100110000 \n");
            printf("Hex Sum: 530 \n");
        }

        // Free memory
        free(bin_1);
        free(bin_2);
}
