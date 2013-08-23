#include"log.h"
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>

#define SERVERS 100
#define MAX_SERVER_HANDLE_TIME 3
#define MAX_REQUESTS 100
#define REQUEST_ISSUE_INTERVAL 1
unsigned int requests = 0;

void* client(void *arg)
{
	pthread_mutex_t *mutex = arg;
	srand((unsigned int)time(NULL));
	while (1) {
		unsigned int incoming = rand()%MAX_REQUESTS;
		pthread_mutex_lock(mutex); /* Will block here till mutex lockable. */
		requests += incoming;
		pthread_mutex_unlock(mutex);
		LOGI("Incoming %u requests",incoming);
		sleep(REQUEST_ISSUE_INTERVAL);
	}
}

void* server(void *arg)
{
	pthread_mutex_t *mutex = arg;
	while (1) {
		if (EBUSY == pthread_mutex_trylock(mutex)) { /* Will lock or exit. */
			LOGI("[%lu] MUTEX BUSY", pthread_self());
		} else {
			if (requests)
				requests--;
			else
				LOGI("[%lu] No request", pthread_self());
			pthread_mutex_unlock(mutex);
			LOGI("[%lu] Fulfill 1 request", pthread_self());
		}
		sleep(rand()%MAX_SERVER_HANDLE_TIME);
	}
}

int main(void)
{
#if 1
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#else /* Same as "#if 1" part. */
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
#endif
	pthread_t ts[SERVERS],tc;
	int i = 0;
	pthread_create(&tc, NULL, client, &mutex);
	for (i = 0; i < SERVERS; i++) {
		pthread_create(ts+i, NULL, server, &mutex);
	}
	pthread_join(tc, NULL);
	return(0);
}
