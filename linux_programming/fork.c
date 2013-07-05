#include<stdio.h>
#include<sys/types.h>

int main(void)
{
	pid_t child_pid;
	printf("main pid = %d\n",getpid());

	child_pid = fork();
	if (child_pid) {
		printf("[parent] pid = %d\n", getpid());
		printf("[parent] parent pid = %d\n", getppid());
	} else {
		printf("[child] pid = %d\n", getpid());
		printf("[child] parent pid = %d\n", getppid());
		/*
		 * Sometimes "[child] parent pid = 1",
		 * because parent was end, thus child became orphan.
		 * Then Init take over it.
		 */
	}
}
