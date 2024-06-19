#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    system("ls *.c | wc");
    return EXIT_SUCCESS;
}