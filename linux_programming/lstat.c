#include"log.h"
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	char *path = "./";
	struct stat buf;
	lstat(path, &buf);
	LOGI("size = %ld\n",buf.st_size);
	return(0);
}
