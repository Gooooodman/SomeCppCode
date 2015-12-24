#include <iostream>
#include <cstring>
/*
	��Interpreter-��һ������,���������ķ���һ�ֱ�ʾ,
	������һ��������,�ý�����ʹ�øñ�ʾ��
	���������еľ���
*/
using namespace std;

/*�ṩ��Ϣ*/
class Context
{
public:
	void SetExpression(char * expression)
	{
		this->expression = expression;
	}
	char * GetExpression()
	{
		return expression;
	}
private:
	char * expression;
};

/*������������*/
class AbsExpression
{
public:
	virtual void Interpret() = 0;
};

/*����������ʵ��֮һ*/
class SimpleExpression : public AbsExpression
{
public:
	void SetContext(Context * context)
	{
		this->context = context;
	}
	/*ģ������������ķ�*/
	void Interpret()
	{
		char * data = context->GetExpression();
		/*�����߼�*/
		if(strcmp(data, "apple") == 0)
		{
			cout << "ƻ��" << endl;
		}
		else if(strcmp(data, "banana") == 0)
		{
			cout << "�㽶" << endl;
		}
	}
private:
	Context * context;
};

int main()
{
	Context * context = new Context;
	context->SetExpression("apple");
	SimpleExpression * expression = new SimpleExpression;
	expression->SetContext(context);
 	
	delete expression;
	delete context;
	return 0;
}
