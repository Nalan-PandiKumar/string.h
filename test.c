#include <stdio.h>
#include "asm_string.h"

int main()
{
	char src[] = "hello world!!";
	char dest[13];
	printf("strlen:%u\n", strlen("hello"));
	strncpy(dest, src,13);
	printf("strcpy:%s\n", dest);
	return 0;
}