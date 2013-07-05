#include<stdio.h>
#include"log.h"

int main(int argc, char *argv[])
{
	LOGI("Demo getpid() & getppid()");
	LOGI("my pid = %d", getpid());
	printf("my pid = %d\n", getpid());
	printf("parent pid = %d\n", getppid());
	return(0);
}
