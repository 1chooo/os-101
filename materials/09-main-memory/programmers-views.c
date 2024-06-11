#include <stdio.h>
#include <math.h>

// Symbol Table
#define PI 3.14159265358979323846

// Subroutine
void subroutine() {
    printf("This is a subroutine.\n");
}

// Main Program
int main() {
    // Local variables (stack)
    double result;
    double number = 9.0;

    // Call to sqrt function
    result = sqrt(number);

    // Print results
    printf("The square root of %.2f is %.2f\n", number, result);

    // Call subroutine
    subroutine();

    return 0;
}
