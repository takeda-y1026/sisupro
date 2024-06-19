#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

char* make_str(int len){ //文字列の作成
    // +1は終端文字('\0')のため
    char *s = (char*)malloc(len + 1); 

    if (s == NULL){
        return NULL; // メモリ確保が失敗した場合の処理
    }

    for (int i = 0; i < len; i++){
        s[i] = 'a';
    }
    s[len] = '\0'; // 文字列終端を示す

    return s;
}

//strlen(const char *s)と同じ動作をする
int main(void){
    clock_t start_clock, end_clock;
    char *s = make_str(1000000000 - 1);
    int slen = 0;
    start_clock = clock();
    for (int i = 0; s[i] != '\0'; i++){
        slen++;
    }
    end_clock = clock();
    double time1 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    start_clock = clock();
    int slen2 = strlen(s);
    end_clock = clock();
    double time2 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    printf("my_strlen1: %d\n", slen);
    printf("time (my_strlen1): %f\n", time1);
    printf("\n");
    printf("strlen: %d\n", slen2);
    printf("time (strlen): %f\n", time2);
    free(s);

    return 0;
}