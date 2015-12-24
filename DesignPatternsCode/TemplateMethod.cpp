#include <iostream>
/*
	TemplateMethod-����������㷨�Ĺ˼�,����һЩ����
	�ӳٵ�������,TemplateMethodʹ��������Բ��ı�һ
	���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض�����
*/
using namespace std;

/*ģ�����ӿ�*/
class AbsClass
{
public:
	virtual void MethodA() = 0;
	virtual void MethodB() = 0;
};

/*ʵ��*/
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
