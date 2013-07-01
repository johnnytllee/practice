#include<iostream>
using namespace std;

void foo(void)
{
	cout<<__PRETTY_FUNCTION__<<endl;
}

void bar(void)
{
	cout<<__PRETTY_FUNCTION__<<endl;
}

class base {
public:
	void foo(void) {
		cout<<__PRETTY_FUNCTION__<<endl;
	}
	void show(void) {
		bar();
		foo();
		::foo();
	}
};

int main(int argc, char *argv[])
{
	base bc;
	bc.show();
	return(0);
}
