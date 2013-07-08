#include"log.h"
#include<signal.h>
#include<string.h>

sig_atomic_t sig_num = 0;
sig_atomic_t sig_cnt = 0;

void sig_handler(int signal_number)
{
	sig_cnt++;
}

int main(void)
{
	struct sigaction sa;
	sig_atomic_t prev_sig_cnt = sig_cnt;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	while (1) {
		if (prev_sig_cnt != sig_cnt) {
			LOGI("sig_cnt = %d", sig_cnt);
			prev_sig_cnt = sig_cnt;
		}
		sleep(1);
	}
	return(0);
}
