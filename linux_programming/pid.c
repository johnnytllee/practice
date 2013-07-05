#include<stdio.h>

int main(int argc, char *argv[])
{
	printf("my pid = %d\n", getpid());
	printf("parent pid = %d\n", getppid());
	return(0);
}
