/*
 * __cplusplus is defined by g++.
 */

#include<stdio.h>

int main(void)
{
#ifdef __cplusplus
	printf("CPP\n");
#else
	printf("C\n");
#endif
}
