#include <iostream>
/*
	ChainofResponsibility-使多个对象都有机会处理请求,
	从而避免请求的发送者和接受者之间的耦合关系,将这些
	对象连成一条链,并沿着这条链传递该请求,直到有一个
	对象处理它为止 
*/
using namespace std;

/*事件抽象接口*/
/*通常配合组合模式使用*/
class AbsEvent
{
public:
	/*处理事件方法*/
	virtual bool OnEvent(int action) = 0;
};

/*员工*/
class Staff : public AbsEvent
{
public:
	bool OnEvent(int action)
	{
		//return false;
		cout << "staff doing" << endl;
		return true;
	}
private:
	int action;
};

/*经理*/
class Manager : public AbsEvent
{
public:
	Manager()
	{
		staff = new Staff;
	}
	~Manager()
	{
		delete staff;
		staff = NULL;
	}
	bool OnEvent(int action)
	{
		if(!staff->OnEvent(action))
		{
			/*...*/
			cout << "manager doing" << endl;
			return true;
		}	
		return true;
	}
private:
	Staff *staff;
};

/*老板*/
class Boss : public AbsEvent
{
public:
	Boss()
	{
		manager = new Manager;
	}
	~Boss()
	{
		delete manager;
		manager = NULL;
	}
	void Doing()
	{
		OnEvent(0);
	}
	bool OnEvent(int action)
	{
		/*判断下级是否处理事件*/
		if(!manager->OnEvent(action))
		{
			 /*...*/
			 cout << "not doing" << endl;
		}
		return false;
	}
private:
	Manager *manager;
	/*other person*/
};

int main()
{
	Boss * boss = new Boss;
	boss->Doing();
	
	delete boss;
	return 0;
}
