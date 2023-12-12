#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char* HexToBinary(char* hexstring, int n_total_bits);

double BinaryToFloat(char* binstring, int n_mantissa_bits, int n_exponent_bits);

void CalculateMinMax(int n_mantissa_bits, int n_exponent_bits);

void AddHex(char *hex1, char *hex2, int n_total_bits, int n_mantissa_bits, int n_exponent_bits);

#endif