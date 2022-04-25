#include <stdio.h>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"

void printProgress(double percentage)
{
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [" GRN "%.*s%*s" RESET "]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}