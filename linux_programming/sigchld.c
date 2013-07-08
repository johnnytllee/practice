#include"log.h"
#include<stdlib.h>
#include<signal.h>
#include<string.h>

sig_atomic_t child_status = 0;
sig_atomic_t signal_number = 0;

void sigchld_hdlr(int sig_num)
{
	wait(&child_status);
	signal_number = sig_num;
}

int main(void)
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigchld_hdlr;
	sigaction(SIGCHLD, &sa, NULL);

	if (fork()) {
		do {
		} while(signal_number == 0);
		LOGI("Received %d, child return %d", signal_number, child_status);
	} else {
		time_t t = time(NULL);
		srand((unsigned int)t);
		return(rand());
	}
	return(0);
}
