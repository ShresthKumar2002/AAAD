#include <stdio.h>

// Structure for output
typedef struct {
    int gcd;
    int x;
    int y;
} Output;

// Function to implement the Extended Euclidean Algorithm using structures
Output extendedEuclid(int a,int b) {
    Output result;
    if (b == 0) {
        result.gcd = a;
        result.x = 1;
        result.y = 0;
        return result;
    } else {
        int i = b;
        int j = a % b;
        Output rResult = extendedEuclid(i,j);

        result.gcd = rResult.gcd;
        result.x = rResult.y;
        result.y = rResult.x - (a / b) * rResult.y;
        return result;
    }
}

int main() {
    int a,b;
    Output calculatedOutput;

    printf("Enter two integers a and b: ");
    scanf("%d %d", &a, &b);
    
    if(a==b)
    {return 0;}
    else if(b>a)
    {
        calculatedOutput = extendedEuclid(b,a);
        printf("gcd(%d, %d) = %d\n", b, a, calculatedOutput.gcd);
        printf("Coefficients x and y such that %d*%d + %d*%d = %d are: x = %d, y = %d\n",
           b, calculatedOutput.x, a, calculatedOutput.y,
           calculatedOutput.gcd, calculatedOutput.x, calculatedOutput.y);
    }
    else
    {
        calculatedOutput = extendedEuclid(a,b);
        printf("gcd(%d, %d) = %d\n", a, b, calculatedOutput.gcd);
        printf("Coefficients x and y such that %d*%d + %d*%d = %d are: x = %d, y = %d\n",
           a, calculatedOutput.x, b, calculatedOutput.y,
           calculatedOutput.gcd, calculatedOutput.x, calculatedOutput.y);
    }
     return 0;
}