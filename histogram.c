#include <stdio.h>
#include <stdlib.h>
#define M 30
#define N 1000

int array[M] = {0};
void generate_random_numbers(int range, int number){
    for (int i = 0; i < N; i++){
        int random_number = (rand() % M) + 1;
        array[random_number - 1]++;
        printf("%d, ", random_number);
    }
    printf("\n\n");
}

int main(void){
    generate_random_numbers(M, N);
    for (int i = 1; i <= M; i++){
        printf("%2d ", i);
        for (int j = 1; j <= array[i-1]; j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}