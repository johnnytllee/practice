#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define container_of(ptr, type, member) ({                      \
        const typeof(((type *)0)->member) * __mptr = (ptr);     \
        (type *)((char *)__mptr - offsetof(type, member)); })

struct base {
	int first_element;
	char second_element;
	struct base *third_element;
};

int print_base(struct base *pBase)
{
	printf("\npBase = %p\n",pBase);
	printf("first_element = %d\n",pBase->first_element);
	printf("second_element = %c\n",pBase->second_element);
	printf("third_element = %p\n",pBase->third_element);
}

int main(void)
{
	base *pBase = (typeof(pBase)) malloc(sizeof(base));
	pBase->first_element = 54068;
	pBase->second_element = 'c';
	pBase->third_element = pBase;

	printf("offsetof(base[%p],1st_element[%p]) = %lu\n",pBase,&(pBase->first_element),offsetof(base,first_element));
	printf("offsetof(base[%p],2nd_element[%p]) = %lu\n",pBase,&(pBase->second_element),offsetof(base,second_element));
	printf("offsetof(base[%p],3rd_element[%p]) = %lu\n",pBase,&(pBase->third_element),offsetof(base,third_element));

	print_base(container_of(&(pBase->first_element),base,first_element));
	print_base(container_of(&(pBase->second_element),base,second_element));
	print_base(container_of(&(pBase->third_element),base,third_element));
	return(0);
}
