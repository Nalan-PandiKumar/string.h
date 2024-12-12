#include <stdio.h>
#include "asm_string.h"

int main()
{

	printf("strcmp:%d\n",strcmp("apple", "banana"));  // Returns a negative value (ASCII 'a' - 'b')
	printf("strcmp:%d\n",strcmp("banana", "apple"));  // Returns a positive value (ASCII 'b' - 'a')

	
	return 0;
}