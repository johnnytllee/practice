#include"log.h"
#include<signal.h>

int main(int argc, char *argv[])
{
	if (argc == 2) {
		kill(atoi(argv[1]), SIGKILL);
	}
	return(0);
}
