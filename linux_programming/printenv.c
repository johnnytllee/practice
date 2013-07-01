#include<stdio.h>

int main(int argc, char *argv[], char *env[])
{
	void **p = (void*)(argv - 1);
	
	int i;

	printf("&argc = [%p] %p\n",&argc,*(&argc));
	printf("&argv = [%p] %p\n",&argv,*(&argv));
	printf("&env  = [%p] %p\n",&env,*(&env));

	printf("[%p] -> [%p]\n",p,*p);
	printf("argc = %d\n",argc);
	for (i = 0; i < argc; i++) {
		printf("[%p] -> [%p] %s\n",&argv[i],argv[i],argv[i]);
	}
#if 0
	printf("[%p] -> [%p]\n",&argv[i],argv[i]);

	i++;	
	while (argv[i]) {
		printf("[%p] -> [%p] %s\n",&argv[i],argv[i],argv[i]);
		i++;
	}
#endif
	i = 0;
	while (env[i]) {
		printf("[%p] -> [%p] %s\n",&env[i],env[i],env[i]);
		i++;
	}

	return(0);
}
