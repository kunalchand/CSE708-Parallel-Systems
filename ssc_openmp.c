#include <stdio.h>
#include <omp.h>
#include <sys/time.h>

void print_1D_Array(int row, int array[row]) {
    int i;
    printf("[");
    for (i = 0; i < row; i++) {
        printf("%d", array[i]);
        if (i < row - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void print_2D_Array(int row, int col, int array[row][col]){
    for(int i=0; i<row; i++){
        printf("Row %d: ", i);
        for(int j=0; j<col; j++){
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}

void initialize_Table_To_Default(int row, int col, int dp[row][col], int thread_table[row][col]){
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            dp[i][j] = 0;
            thread_table[i][j] = omp_get_thread_num();
        }
    }
}

void subsetSumCount(int a[], int n, int sum) {
    // DP Table & Thread Table
    int dp[n + 1][sum + 1];
    int thread_table[n + 1][sum + 1];
    
    initialize_Table_To_Default(n+1, sum+1, dp, thread_table);

    // Initialize Top Row
    dp[0][0] = 1;
    thread_table[0][0] = omp_get_thread_num();
    for (int j = 1; j <= sum; j++){
        dp[0][j] = 0;
        thread_table[0][j] = omp_get_thread_num();
    }

    unsigned long long usec;
    struct timeval tstart, tend;

    gettimeofday(&tstart, NULL);

    // Row Wise Iteration
    for (int i = 1; i <= n; i++) {        
        #pragma omp parallel for
        for (int j = 0; j <= sum; j++) {
            // Fill Thread Table to keep track         
            int thread_id = omp_get_thread_num();
            thread_table[i][j] = thread_id;

            // Core DP Logic
            if (a[i - 1] > j){
                #pragma omp atomic write
                dp[i][j] = dp[i - 1][j];
            } 
            else {
                int temp = dp[i - 1][j] + dp[i - 1][j - a[i - 1]];
                #pragma omp atomic write
                dp[i][j] = temp;
            }
        }
    }

    gettimeofday(&tend, NULL);

    printf("\nThread Table: \n");
    print_2D_Array(n+1, sum+1, thread_table);
    
    printf("\nDP Table: \n");
    print_2D_Array(n+1, sum+1, dp);

    printf("\n");

    printf("Subset Sum Count = %d\n", dp[n][sum]);

    if (tend.tv_usec > tstart.tv_usec){
        usec = (tend.tv_sec - tstart.tv_sec) * 1000000 + tend.tv_usec - tstart.tv_usec;
    } 
    else{
        usec = (tend.tv_sec - (tstart.tv_sec + 1)) * 1000000 + (1000000 + tend.tv_usec - tstart.tv_usec);
    }

    printf("\nFinished in %f seconds.\n",(double)usec/1000000.0);
}

int main() {
    int n = 5;
    int input[] = {3, 1, 2, 4, 5};
    int sum = 6;

    int max_threads = omp_get_max_threads();
    printf("Max Threads = %d\n\n", max_threads);

    printf("Input Array = ");
    print_1D_Array(n, input);
    printf("Target Sum = %d\n", sum);
    
    subsetSumCount(input, n, sum);

    return 0;
}
