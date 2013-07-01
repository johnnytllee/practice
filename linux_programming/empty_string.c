#include<stdio.h>
#include<string.h>

int main(void)
{
	char empty_str[] = "";
	char null_str[] = "\0";
	int result = 0;

	printf("strlen(empty_str) = %lu\n",strlen(empty_str));
	printf("strlen(null_str) = %lu\n",strlen(null_str));
	result = strcmp(empty_str, null_str);
	printf("strcmp(empty_str, null_str) = %d\n",result);
	if (empty_str[0] == null_str[0])
		printf("empty_str[0] == null_str[0]\n");
	return(0);
}
