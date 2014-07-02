#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define REATTACH_ADDR 0x5000000

int main ()
{
	int segment_id = 0;
	char* shared_memory = NULL;
	struct shmid_ds shmbuffer;
	int segment_size = 0;
	const int shared_segment_size = getpagesize();//0x6400;
	/* Allocate a shared memory segment.  */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,
		IPC_CREAT |  IPC_EXCL |  S_IRUSR |  S_IWUSR);
	/* Attach the shared memory segment.  */
	shared_memory = (char*) shmat (segment_id, 0, 0);
	printf ("shared memory attached at address %p\n", shared_memory);
	/* Determine the segment’s size.  */
	shmctl (segment_id, IPC_STAT, &shmbuffer);
	segment_size = shmbuffer.shm_segsz;
	printf ("segment size: %d\n", segment_size);
	/* Write a string to the shared memory segment.  */
	sprintf (shared_memory, "Hello, world.");
	system("ipcs -m");
	/* Detach the shared memory segment.  */
	shmdt (shared_memory);

	system("ipcs -m");
//	printf ("[%p]%c\n", (void*)shared_memory, (int)*((char*)REATTACH_ADDR));
//	printf ("[%p]%c\n", (void*)REATTACH_ADDR, (int)*((char*)REATTACH_ADDR));

	/* Reattach the shared memory segment, at a different address.  */
	shared_memory = (char*) shmat (segment_id, (void*) REATTACH_ADDR, 0);
	printf ("shared memory reattached at address %p\n", shared_memory);
	/* Print out the string from shared memory.  */
	printf ("%s\n", shared_memory);
	/* Detach the shared memory segment.  */
	shmdt (shared_memory);
	system("ipcs -m");
	/* Deallocate the shared memory segment.  */
	shmctl (segment_id, IPC_RMID, 0);
	system("ipcs -m");
	return 0;
}
