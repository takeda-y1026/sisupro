#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    char c;
    int fps, fpd;
    int count;

    //1文字ごとに
    fps = open("10-mb-file.txt", O_RDONLY);
    if (fps < 0) {
        perror("open: src: ");
        exit(1);
    }

    fpd = open("output1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror("open: dst: ");
        close(fps);
        exit(1);
    }

    clock_t start_clock, end_clock;
    start_clock = clock();
    while ((count = read(fps, &c, 1)) > 0) {
        if (write(fpd, &c, count) < 0) {
            perror("write");
            close(fpd);
            close(fps);
            exit(1);
        }
    }

    if (count < 0) {
        perror("read");
        close(fpd);
        close(fps);
        exit(1);
    }
    //ここまでは1文字ごと
    end_clock = clock();
    double time1 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;

    close(fpd);
    close(fps);
    
    

    //BUFSIZ文字ごとに
    char buffer[BUFSIZ];

    fps = open("10-mb-file.txt", O_RDONLY);
    if (fps < 0) {
        perror("open: src: ");
        exit(1);
    }

    fpd = open("output2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror("open: dst: ");
        close(fps);
        exit(1);
    }

    start_clock = clock();
    while ((count = read(fps, buffer, BUFSIZ)) > 0) {
        if (write(fpd, buffer, count) < 0) {
            perror("write");
            close(fpd);
            close(fps);
            exit(1);
        }
    }

    if (count < 0) {
        perror("read");
        close(fpd);
        close(fps);
        exit(1);
    }
    //ここまではBUFSIZ文字ごと
    end_clock = clock();
    double time2 = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;

    printf("time (one letter): %f\n", time1);
    printf("time (BUFSIZ letters): %f\n", time2);

    close(fpd);
    close(fps);

    return 0;
}