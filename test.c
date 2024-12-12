#include <stdio.h>
#include "asm_string.h"

int main()
{

	char dest[] = "Nalan";
	char src[] = "";
	char* str = strncat(dest, src,13);
	printf("strncat:%s",str);
	free(str);
	
	return 0;
}