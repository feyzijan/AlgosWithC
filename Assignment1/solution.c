#include <stdio.h>
#include <math.h>

#define MaxIterations 50
#define Tolerance 1e-10

/*42*y
status:
    0: success
    1: max iterations reached
    2: singular jacobian
    3: negative in sqrt
    4: not implemented
*/

void newton_method(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;

    // Declare variables for the functions f and g, and the previous x and y values
    double f;
    double g;
    double x_old;
    double y_old;

    //printf("Newtons iteration started with x_0 = %lf, y_0 = %lf\n", *x, *y); // Debug line - print initial values

    // Loop until max iterations is reached unless we need to return earlier
    while (*iterations < MaxIterations){

        (*iterations)++; // Increment iteration counter

        // Calculate the denominator term in the Jacobian's inverse to see if it is euqal to 0
        // if so jacobian is singular and we return
        double denominator = (2.0 * (*x) * 42.0* (*y)) - (2.0* (*y) * 10.0* (*x));
        if (denominator == 0){
            *status = 2;
            return;
        }

        // Calculate f and g
        f = ( (*x) * (*x) ) + ( (*y) * (*y) ) - 1.0;
        g =  5.0 * ( (*x) * (*x) ) + 21.0 * ( (*y) * (*y) ) - 9.0;

        // Update the previous x and y values to compute tolerance later on
        x_old = *x;
        y_old = *y;

        // Calculate new x and y values using Newtons Iteration
        *x = *x -  (1.0 /denominator)  * ( 42.0 * (*y) * f  - 2.0 * (*y) * g);
        *y = *y -  (1.0 /denominator)  * ( -10.0 * (*x) * f  + 2.0 * (*x) * g);

        // Check if tolerance is met, if so return
        if ((fabs(*x - x_old) < Tolerance) && (fabs(*y - y_old) < Tolerance)){
            *status = 0;
            //printf("Newtons tolerance met\n"); // Debug line
            return;
        }

        // Debug lines
        //printf("Newtons iteration no %d: x = %.10f, y = %.10f\n", *iterations, *x, *y);
        //printf("\t Abs changes are dx = %.10f, dy = %.10f\n", fabs(*x - x_old), fabs(*y - y_old)); 

    }

    *status = 1; // max iterations reached, exit with status 1
    return;

    //printf("Newton method finished:\n");
}

void fixed_point_iteration(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;

    // Declare variables for the previous x and y values
    double x_old;
    double y_old;

    // Debug line - print initial values
    //printf("\nFixed point iteration started with x_0 = %lf, y_0 = %lf\n", *x, *y);

    while (*iterations < MaxIterations){
        
        (*iterations)++; // Increment iteration counter

        // Check if inside of square roots will be negative, if so return
        if ( (1.0 - ((*y)*(*y)) < 0.0) || ((9.0 - 5.0 * (*x)*(*x)) < 0.0) ){
            //printf("Fixed point iteration failed, negative in sqrt\n");
            //printf(" left sqrt : %lf, right sqrt: = %lf\n", (1.0 - (*y)*(*y)), (9.0 - 5.0 * (*x)*(*x)) );
            *status = 3;
            return;
        }

        // Update the previous x and y values to compute tolerance
        x_old = *x;
        y_old = *y;

        // Calculate new x and y values 
        //!! Use x_old and y_old since we need the previous values to calculate new ones
        *x = sqrt(1.0 - (y_old)*(y_old));
        *y = sqrt( (9.0 - 5.0*(x_old)*(x_old)) / 21.0);

        // Check if tolerance is met
        if (fabs(*x - x_old) < Tolerance && fabs(*y - y_old) < Tolerance){
            *status = 0;
            //printf("Fixed point iteration tolerance met \n"); // Debug line
            return;
        }
        
        // Debug lines
        //printf("Fixed point iteration no %d: x = %.10f, y = %.10f\n", *iterations, *x, *y);
        //printf("\t Abs changes are dx = %.10f, dy = %.10f\n", fabs(*x - x_old), fabs(*y - y_old)); 

    }
    *status = 1; // max iterations reached, exit with status 1
    return;

}
