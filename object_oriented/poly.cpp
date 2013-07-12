#include<iostream>
#include<stdio.h>
#include<typeinfo>
using namespace std; 
class base {
public:
        enum baseType {
                type1 = 0,
                type2
        };
	base(){cout<<__PRETTY_FUNCTION__<<endl;}
	virtual ~base(){cout<<__PRETTY_FUNCTION__<<endl;}
	virtual void show(void){cout<<__PRETTY_FUNCTION__<<endl;}
	//void show(void){cout<<__PRETTY_FUNCTION__<<endl;}
	base *getThis(void){return(this);}
};

class derived1 : public base {
public:
	derived1 *_this;
	derived1(){cout<<__PRETTY_FUNCTION__<<endl;}
	~derived1(){cout<<__PRETTY_FUNCTION__<<endl;}
	void show(void){cout<<__PRETTY_FUNCTION__<<endl;}
	derived1 *getThis(void){return(this);}
};

class derived2 : public base {
public:
	derived2(){cout<<__PRETTY_FUNCTION__<<endl;}
	~derived2(){cout<<__PRETTY_FUNCTION__<<endl;}
	void show(void){cout<<__PRETTY_FUNCTION__<<endl;}
};

base *getObj(int type)
{
	base *pObj = NULL;
	switch (type) {
	case base::type1: pObj = new derived1(); break;
	case base::type2: pObj = new derived2(); break;
	}
	return(pObj);
}

void relObj(void *rObj)
{
	base *dpObj = (base*)rObj;
	dpObj->show();
#if 0
	cout<<typeid(*dpObj).name()<<endl;
	cout<<typeid(derived1).name()<<endl;
	delete((base*)rObj);
	if (typeid(*dpObj)==typeid(derived1)) delete (derived1*)dpObj;
	else if (typeid(*dpObj)==typeid(derived2)) delete (derived2*)dpObj;
	else delete dpObj;
#elif 1
	if (derived1 *inst=dynamic_cast<derived1*>(dpObj)) delete inst;
	else if (derived2 *inst=dynamic_cast<derived2*>(dpObj)) delete inst;
	else delete dpObj;
#endif
}

int main(int argc, char *argv[])
{
#if 1
	base *d1 = new derived1();
	derived2 d2;
	if (d1==d1->getThis())
		cout<<"d1==d1->getThis()"<<endl;
	else
		cout<<"d1!=d1->getThis()"<<endl;
	d1->show();
	delete d1;
#else
	derived1 *d1 = (derived1*)getObj(0);
	relObj((void*)d1);
#endif
	return 0;
}
