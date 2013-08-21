#include "log.h"
#include <time.h>
#include <signal.h>
#include <string.h>

static void timeout_notify_me(union sigval arg)
{
	LOGI("");
}
 
int main(void)
{
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 1;
	its.it_interval.tv_nsec = 0;
	memset(&sev, 0, sizeof(sev));
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = timeout_notify_me;
	int ret_val = 0;
	ret_val = timer_create(CLOCK_REALTIME, &sev, &timerid);
	if (ret_val) {
		LOGI("timer_create return (%d)", ret_val);
		goto hell;
	}
	LOGI("timerid = %lu",(long)timerid);
	ret_val = timer_settime(timerid, 0, &its, NULL);
	if (ret_val) {
		LOGI("timer_settime return (%d)", ret_val);
		goto hell;
	}
	sleep(100);
hell:
	return(0);
}
