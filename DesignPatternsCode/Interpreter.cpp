#include <iostream>
#include <cstring>
/*
	给Interpreter-定一个语言,定义它的文法的一种表示,
	并定义一个解释器,该解释器使用该表示来
	解释语言中的句子
*/
using namespace std;

/*提供信息*/
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

/*解释器抽象类*/
class AbsExpression
{
public:
	virtual void Interpret() = 0;
};

/*解释器具体实现之一*/
class SimpleExpression : public AbsExpression
{
public:
	void SetContext(Context * context)
	{
		this->context = context;
	}
	/*模拟解释器解释文法*/
	void Interpret()
	{
		char * data = context->GetExpression();
		/*解释逻辑*/
		if(strcmp(data, "apple") == 0)
		{
			cout << "苹果" << endl;
		}
		else if(strcmp(data, "banana") == 0)
		{
			cout << "香蕉" << endl;
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
