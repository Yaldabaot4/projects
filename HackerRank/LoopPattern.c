#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n = 4;
    int plength = 2 * n - 1;
    int change = 0;
    for (unsigned int i = 0; i < plength; i++) {
        for (unsigned int j = 0; j < plength; j++) {
            printf("%d ", n - change);
            if (i > j) {
                change++;
            }
            if (i + 1 >= plength - j) {
                change--;
            }
        }
        change = 0;
        printf("\n");
    }
    return 0;
}