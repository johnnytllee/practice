#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

const struct option my_options_1[] = {
	{"alpha", no_argument, NULL, 'a'},
	{"bravo", no_argument, NULL, 'b'},
	{"charlie", no_argument, NULL, 'c'},
	{NULL, 0, NULL, 0}
};
const char *opt1 = "abc";

const struct option my_options_2[] = {
	{"xray", no_argument, NULL, 'x'},
	{"yankee", no_argument, NULL, 'y'},
	{"zulu", no_argument, NULL, 'z'},
	{NULL, 0, NULL, 0}
};
const char *opt2 = "xyz";

struct base_option {
	const struct option *longopts;
	const char *optstring;
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
	struct base_option *my_option = NULL;
	my_option = malloc(sizeof(*my_option));
	my_option->longopts = my_options_1;
	my_option->optstring = opt1;
	my_getopt(my_option, getpid(), argc, argv);
	free(my_option);
	return(0);
}
