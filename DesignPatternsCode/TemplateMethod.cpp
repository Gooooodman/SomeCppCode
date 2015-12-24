#include <iostream>
/*
	TemplateMethod-定义操作中算法的顾家,而将一些步骤
	延迟到子类中,TemplateMethod使得子类可以不改变一
	个算法的结构即可重定义该算法的某些特定步骤
*/
using namespace std;

/*模版抽象接口*/
class AbsClass
{
public:
	virtual void MethodA() = 0;
	virtual void MethodB() = 0;
};

/*实现*/
class ConClass : public AbsClass{
public:
	void MethodA()
	{
		cout << "MethodA" << endl;
	}
	void MethodB()
	{
		cout << "MethodB" << endl;
	}
	/*...*/
};

int main()
{
	AbsClass * c = new ConClass;
	c->MethodA();
	c->MethodB();
	
	delete c;
	return 0;
}
