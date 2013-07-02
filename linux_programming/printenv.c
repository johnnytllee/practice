#include<stdio.h>
#include<stdlib.h>

extern char **environ;

void use_env(char *env[])
{
	int i = 0;
	printf("\n\nVia char *env[]\n");
	while (env[i]) {
		printf("[%p] -> [%p] %s\n",&env[i],env[i],env[i]);
		i++;
	}
}

void use_environ(void)
{
	char **p = environ;
	printf("\n\nVia extern char **environ;\n");
	while (*p) {
		printf("[%p] -> [%p] %s\n",p,*p,*p);
		p++;
	}
}

void use_getenv(const char *env_name)
{
	char *env = getenv(env_name);
	printf("%s=%s\n",env_name,env?env:"");
}

int main(int argc, char *argv[], char *env[])
{
	void **p = (void*)(argv - 1);
	
	int i;

	printf("&argc = [%p] %d\n",&argc,*(&argc));
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
	use_env(env);
	use_environ();

	printf("\n\nDemo getenv\n");
	use_getenv("PWD");
	use_getenv("");
	use_getenv("SHIT");

	return(0);
}
