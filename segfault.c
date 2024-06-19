#include <stdio.h>

void access_pointer(char *p)
{
        printf("%c", *p);
}

void test(void)
{
        access_pointer(NULL);
}


int main(void)
{
        test();
        return 0;
}