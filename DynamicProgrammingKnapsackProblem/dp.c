#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char * argv[]){

    // Read file contents
    char * input_file = argv[1];
    FILE * file = fopen(input_file, "r");

    // Get size
    int n;
    fscanf(file, "%d", &n);


    // Create array to store prıces
    int * p_arr = malloc((n+1) * sizeof(int));
    for (int i=1; i<=n; i++){
        fscanf(file, "%d", &p_arr[i]);
    }

    fclose(file);

    // Create array to store best results
    int * best_arr = malloc((n+1) * sizeof(int));
    // Create array to store the batter used
    int * batter_arr = malloc((n+1) * sizeof(int));

    //optionally initialize with memset
    memset(best_arr, 0, (n+1) * sizeof(int));
    memset(batter_arr, 0, (n+1) * sizeof(int));



    // Now do the loop starting from p=1
    // j is used to check the price we can get from using j batters
    // i-j is used to access the best result from using i-j batters
    for (int i=1; i<=n; i++){ // go from 0 to n ( 1 to n in real prices)
        int temp_best = 0;
        int temp_batter = 0;
        for (int j=1; j<=i; j++){
            int candidate = best_arr[i-j] + p_arr[j];
            if (candidate > temp_best){
                temp_best = candidate;
                temp_batter = j;
            }
        }
        best_arr[i] = temp_best;
        batter_arr[i] = temp_batter;
    }



    // print result based on args
    printf("%d", best_arr[n]);
    
    // print the batters used by looping back
    if (argc == 3 && strcmp(argv[2],"d") == 0){
        printf("\n");
        int i = n; // remaining batter 
        while (i > 0){
            printf("%d ", batter_arr[i]); // print the batter used
            i = i - batter_arr[i]; 
        }
    }

    // Free memory
    free(p_arr);
    free(best_arr);
    free(batter_arr);

    return 0;
}