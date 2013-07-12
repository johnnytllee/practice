#include"log.h"
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

struct thread_arg {
	const char *name;
	unsigned int times;
};

void foo(void *arg)
{
	struct thread_arg *targ = arg;
	unsigned int i = targ->times;
	do {
		LOGI("[%lu] %d %s", pthread_self(), i, targ->name);
		sleep(1); /* sleep() is a cancellation point. */
	} while (i--); 
}

void* t1(void *arg)
{
	foo(arg);
	return(arg);
}

void* t2(void *arg)
{
	int ret_val = 0;
	LOGI("self pthread_cancel");
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	// ret_val = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	ret_val = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	LOGI("pthread_setcanceltype returns (%d)%s", ret_val, strerror(ret_val));
	ret_val = pthread_cancel(pthread_self());
	/* If PTHREAD_CANCEL_ASYNCHRONOUS, this thread should be terminated immediately, but not guranteed. */
	LOGI("pthread_cancel returns (%d)%s", ret_val, strerror(ret_val)); /* printf() is a cancellation point. */
	// pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	/* Thread was cancelled. Thus stop here and will not run following code. */
	foo(arg);
	return(arg);
}

void* t3(void *arg)
{
#if 1
	/* This makes other thread end. Because this program is ending. */
	execlp("ls", "ls", NULL);
#else
	sleep(1);
	if (fork()) {
		foo(__func__);
	} else {
		LOGI("ls");
		execlp("ls", "ls", NULL);
	}
#endif
}

static pthread_key_t pkey;
#define T4_CNT 5

void* t4(void *arg)
{
	if (arg) {
		struct thread_arg *targ = arg;
		pthread_setspecific(pkey, arg);
		LOGI("[%lu] [%s] arg = %p", pthread_self(), targ->name, arg);
		LOGI("[%lu] [%s] pkey = %d", pthread_self(), targ->name, pkey);
		LOGI("[%lu] [%s] pkey -> %p", pthread_self(), targ->name, pthread_getspecific(pkey));
	}
}

void pkey_cleanup(void *arg)
{
	struct thread_arg *targ = arg;
	LOGI("[%lu] [%s] arg = %p", pthread_self(), targ->name, arg);
}

/* Thread t4 is to demo the usage of pthread_key_t. */
void pre_t4(void)
{
	const char * const t4name[T4_CNT] = {"A", "B", "C", "D", "E"};
	pthread_t t4t[T4_CNT]; 
	struct thread_arg t4arg[T4_CNT];
	int i = 0;
	LOGI("");
	pthread_key_create( &pkey, pkey_cleanup);
	srand((unsigned int)time(NULL));
	for (i = 0; i<T4_CNT; i++) {
		t4arg[i].name = t4name[i];
		t4arg[i].times = rand()%10 + 1;
		pthread_create(t4t+i, NULL, t4, t4arg+i);
	}
	for (i = 0; i<T4_CNT; i++)
		pthread_join(t4t[i], NULL);
}

void t5_cleanup(void *arg)
{
	struct thread_arg *targ = arg;
	LOGI("[%lu] [%s] arg = %p", pthread_self(), targ->name, arg);
}

void* t5(void *arg)
{
	pthread_cleanup_push(t5_cleanup, arg);
	
	do {
#if 1 
		/* Wait to be cancelled. */
#else
		/* Exit myself. */
		break;
#endif
		sleep(1);
	} while(1);

	pthread_cleanup_pop(1);
}

void pre_t5(void)
{
	pthread_t t5t;
	int ret_val = 0;
	struct thread_arg t5a = {"t5a", 7835};
	pthread_create(&t5t, NULL, t5, &t5a);
	sleep(1);
	ret_val = pthread_cancel(t5t);
	LOGI("pthread_cancel returns (%d)%s", ret_val, strerror(ret_val));
	/* Process may be ended before cleanup, thus wait a moment. */
	sleep(2);
}

void pre_t123(void)
{
	int ret_val = 0;
	pthread_t ptt1a, ptt1b, ptt2, ptt3;
	/* Thread arguments should remain vaild while thread running. */
	struct thread_arg ta1a, ta1b, ta2;
	void *ret = NULL;
	/* Thread attributes only accessed while creating thread. */
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	srand((unsigned int)time(NULL));
	ta1a.name = "t1a";
	ta1a.times = rand()%10 + 1;
	ta1b.name = "t1b";
	ta1b.times = rand()%10 + 1;
	ta2.name = "t2";
	ta2.times = rand()%10 + 1;

	pthread_create(&ptt1a, NULL, t1, &ta1a);
	pthread_create(&ptt1b, &attr, t1, &ta1b);
	pthread_create(&ptt2, NULL, t2, &ta2);

#if 0
	if (argc!=1)
		pthread_create(&ptt3, NULL, t3, NULL);
#endif
	LOGI("Hello Main");
	LOGI("&ta1a = %p", &ta1a);
	LOGI("&ta1b = %p", &ta1b);
	LOGI("&ta2 =%p", &ta2);
	ret = NULL;
	ret_val = pthread_join(ptt1a, &ret);
	LOGI("joined %s return (%d)%s [%p]", ta1a.name, ret_val, strerror(ret_val), ret);
	ret = NULL;
	ret_val = pthread_join(ptt1b, &ret);
	LOGI("joined %s return (%d)%s [%p]", ta1b.name, ret_val, strerror(ret_val), ret);
	ret = NULL;
	ret_val = pthread_join(ptt2, &ret);
	LOGI("joined %s return (%d)%s [%p]", ta2.name, ret_val, strerror(ret_val), ret);
	pthread_attr_destroy (&attr);
}

int main(int argc, char *argv[])
{
	// pre_t4();

	pre_t5();

	return(0);
}
