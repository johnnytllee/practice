#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<string.h>

struct option my_options_1[] = {
	{"alpha", no_argument, NULL, 'a'},
	{"bravo", required_argument, NULL, 'b'},
	{"charlie", no_argument, NULL, 'c'},
	{NULL, 0, NULL, 0}
};
char *opt1 = "ab:c";

struct option my_options_2[] = {
	{"xray", no_argument, NULL, 'x'},
	{"yankee", no_argument, NULL, 'y'},
	{"zulu", no_argument, NULL, 'z'},
	{NULL, 0, NULL, 0}
};
char *opt2 = "xyz";

struct base_option {
	struct option *longopts;
	char *optstring;
};

struct my_derived_option {
	struct base_option *_base_option;
	int opt_c_flag;
};

int my_getopt(struct base_option *this, int pid, int argc, char *argv[])
{
	while (1) {
		int option_index = 0;
		char opt = 0;
		printf("\n[pid=%d] Before: optarg = %s, optind = %d\n", pid, optarg, optind);
		opt = getopt_long(argc, argv, this->optstring, this->longopts, &option_index);
		printf("[pid=%d] After: optarg = %s, optind = %d\n", pid, optarg, optind);
		if (opt == EOF)
			break;
		switch (opt) {
		default:
			printf("[pid=%d] Options += -%c\n", pid, opt);
			break;
		}
//		sleep(10);
	}
	return(0);
}

int main(int argc, char *argv[])
{
	struct my_derived_option *my_option = NULL;
	my_option = malloc(sizeof(*my_option));
	memset(my_option,0,sizeof(*my_option));
	my_option->_base_option = malloc(sizeof(*(my_option->_base_option)));
	my_option->_base_option->longopts = my_options_1;
	my_options_1[2].flag = &(my_option->opt_c_flag);
	my_option->_base_option->optstring = opt1;
	my_getopt((struct base_option*)my_option->_base_option, getpid(), argc, argv);
	printf("my_option->opt_c_flag = %d(%c)\n",my_option->opt_c_flag, my_option->opt_c_flag);
	free(my_option->_base_option);
	free(my_option);
	return(0);
}
