#include <stdio.h>

int inData[] = {10, 10, 10};

int main() {

    int a = inData[0];
    int b = inData[1];
	int c = inData[2];
    int total = a * b + c + a + b - a*b*c + b*b + c*c; // orig
	//  int total = a * b + c + a + b - a*b*c + a*a + c*c;//cor and ch
    printf("Result: %d\n", total);
    if (total == 30) {
        printf("RESULT: PASS\n");
    } else {
        printf("RESULT: FAIL\n");
    }
    return total;
}

