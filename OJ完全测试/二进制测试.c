#include <stdio.h>
#include <stdlib.h>

int main4()
{
	unsigned char test = 11000000;
	char s[10];
	unsigned char a = test >> 6;
	printf("%hhu\n", a);
	printf("%hhu", test);

	return 0;
}