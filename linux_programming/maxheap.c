#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[], char *env[])
{
	unsigned int size[] = {1, 1024, 1024*1024, 1024*1024*1024};
	unsigned long long maxheap = 0;
	unsigned long long l_maxheap = 0;
	void *p = 0;
	int i = 0, j = 0, k=0;
	for (i = (sizeof(size)/sizeof(*size))-1; i>=0; i--) {
		l_maxheap = 0;
		j = 0;
//		printf("%d\n",i);
		while ((p = malloc(size[i]))){
			j++;
			l_maxheap += size[i];
			if (argc>1) {
				for (k = 0; k<size[i]; k++)
					printf("%02x ",*(((char*)p)+k));
			}
		}
		printf("l_maxheap = 1024^%d * %d = %llu\n", i, j, l_maxheap);
		maxheap += l_maxheap;
	}
	printf("maxheap = %llu\n",maxheap);
	return(0);
}
