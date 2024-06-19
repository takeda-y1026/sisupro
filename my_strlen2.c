#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

char* make_str(int len){ //文字列の作成
    char *s = (char*)malloc(len + 1); 

    if (s == NULL){
        return NULL; // メモリ確保が失敗した場合
    }

    for (int i = 0; i < len; i++){
        s[i] = 'a';
    }
    s[len] = '\0';

    return s;
}

bool contains_zero_byte(uint64_t v){ //64ビット整数にゼロバイトが含まれているかどうかをチェック
    uint64_t hi = 0x8080808080808080;
    uint64_t lo = 0x0101010101010101;
    return ((v - lo) & ~v & hi) != 0;
}

int my_strlen2(const char *s){
    const char *start = s;
    while (((uintptr_t)s & 7) != 0){ // Align the pointer to the next multiple of 8
        if (*s == '\0') return s - start;
        s++;
    }

    const uint64_t *word_ptr = (const uint64_t *)s; // Check 64-bit chunks
    while (!contains_zero_byte(*word_ptr)){
        word_ptr++;
    }

    s = (const char *)word_ptr;     // Check the remaining bytes
    while (*s != '\0'){
        s++;
    }

    return (int)(s - start);
}

int main(void){
    clock_t start_clock, end_clock;
    char *s = make_str(1000000000 - 1);

    start_clock = clock();
    int slen1 = my_strlen2(s);
    end_clock = clock();
    double time1 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;

    start_clock = clock();
    int slen2 = strlen(s);
    end_clock = clock();
    double time2 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;

    printf("my_strlen2: %d\n", slen1);
    printf("time (my_strlen2): %f\n", time1);
    printf("\n");
    printf("strlen: %d\n", slen2);
    printf("time (strlen): %f\n", time2);

    free(s);
    return 0;
}
