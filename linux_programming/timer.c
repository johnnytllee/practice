#include "log.h"
#include <time.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

static sem_t sema;
static sem_t sema_2;

static void timeout_notify_me(union sigval arg)
{
	LOGI("");
	sem_post(&sema);
}

static void* worker(void *arg)
{
	while (1) {
		LOGI("");
		sem_wait(&sema);
		LOGI("");
		sem_post(&sema_2);
	}
}

static void* worker2(void *arg)
{
	int ret_val = 0;
	while (1) {
		LOGI("");
		ret_val = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		if (ret_val)
			LOGI("pthread_setcancelstate return (%d)", ret_val);
		LOGI("");
		sem_wait(&sema_2);
		LOGI("");
		ret_val = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		if (ret_val)
			LOGI("pthread_setcancelstate return (%d)", ret_val);
		usleep(1);
	}
}

int main(void)
{
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	pthread_t worker_thread;
	pthread_t worker2_thread;
	int ret_val = 0;
	ret_val = sem_init(&sema, 0, 0);
	if (ret_val) {
		LOGI("sem_init return (%d)", ret_val);
		goto hell;
	}
	ret_val = sem_init(&sema_2, 0, 0);
	if (ret_val) {
		LOGI("sem_init return (%d)", ret_val);
		goto hell;
	}
	ret_val = pthread_create(&worker_thread, NULL, worker, NULL);
	if (ret_val) {
		LOGI("pthread_create return (%d)", ret_val);
		goto hell;
	}
	ret_val = pthread_create(&worker2_thread, NULL, worker2, NULL);
	if (ret_val) {
		LOGI("pthread_create return (%d)", ret_val);
		goto hell;
	}
	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 1;
	its.it_interval.tv_nsec = 0;
	memset(&sev, 0, sizeof(sev));
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = timeout_notify_me;
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
	ret_val = pthread_cancel(worker2_thread);
	if (ret_val) {
		LOGI("pthread_cancel return (%d)", ret_val);
		goto hell;
	}
	ret_val = pthread_join(worker2_thread, NULL);
	if (ret_val) {
		LOGI("pthread_join return (%d)", ret_val);
		goto hell;
	}
	sleep(100);
hell:
	return(0);
}
