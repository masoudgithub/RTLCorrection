/* AddOpr*/
#include <stdio.h>

int inData[] = {10, 10, 10, 10, 10, 10, 10};

int main()
{

 	int a = inData[0];
    int b = inData[1];
	int c = inData[2];
	int d = inData[3];
	int e = inData[4];
	int x = inData[5];
	int y = inData[6];

	int h= a*x*x + b*y*y + c*x*y+ d*x + e*y + a*y*y + a*x + b + c*d + e;//org /* " d*e + x*y" added*/
    printf("Result: %d\n", h);
    if (h == 3200) {
        printf("RESULT: PASS\n");
    } else {
        printf("RESULT: FAIL\n");
    }
    return h;
}
