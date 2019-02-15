#include <stdio.h>

/*#define abs(a) ( ((a) < 0) ? -(a) : (a) )
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )*/

int inData[] = {10, 10, 10};

// square-root approximation:
int main() {

    // sqrt(52^2 + 84^2) = 98.79
    // This should be approximated as 100
    int a = inData[0];
    int b = inData[1];
	int c = inData[2];
    /*int x = max(abs(a), abs(b));
    int y = min(abs(a), abs(b));
    int sqrt = max(x, x-(x>>3)+(y>>1));*/
	//int total = f * g + h - f*g*h ;
	
	//int total = a * b + c + a + b - a*b*c + b*b + c*c; // orig
	int total = c + a + a * b +  b - a*b*c + a*a + c*c;//cor and ch
    printf("Result: %d\n", total);
    if (total == 30) {
        printf("RESULT: PASS\n");
    } else {
        printf("RESULT: FAIL\n");
    }
    return total;
}

