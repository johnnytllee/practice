#include"log.h"
#include<stdio.h>

int spawn(char *const argv[])
{
	if (0 == fork()) {
		return(execv(argv[0], argv));
	}
	else {
		LOGI("Spawn %s",argv[0]);
		return(0);
	}
}

int main(int argc, char *const argv[])
{
	char *const pg_argv[] = { "./jenv", "shit", "happens", NULL};
	if (argc == 1)
		return(spawn(pg_argv));
	else
		return(spawn(argv+1));
}
