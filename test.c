#include <stdio.h>
#include "asm_string.h"

int main()
{
	char src[] = "hel";
	char dest[13];
	printf("strlen:%u\n", strlen("hello"));
	strncpy(dest, src,5);
	printf("strncpy:%s\n", dest);
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", *(dest + i));
	}
	//char dest[] = "Nalan";
	//char src[] = "PandiKumar";
	//char* str = strcat(dest, src);
	//printf("strcat:%s",str);
	//free(str);
	
	return 0;
}