#include <iostream>
/*
	Mediator-用一个对象来封装一系列的对象交互.
	中介者使各对象不需要显式的相互引用,从而使其
	耦合松散,而且可以独立的改变他们之间的交互
*/
using namespace std;

/*同事抽象接口*/
class AbsColleagus
{
public:
	void SetData(char * data)
	{
		this->data = data;
	}
	virtual void Receive(char * info) = 0;
	virtual char * GetData()
	{
		return data;
	}
private:
	char * data;
};

/*信息中介者抽象接口*/
class AbsMediator
{
public:
	virtual void SendMssageTo(AbsColleagus * from, AbsColleagus * to) = 0;
};

/*公司中介者实现*/
class CompanyMediator : public AbsMediator
{
public:
	/*实现两者通信*/
	void SendMssageTo(AbsColleagus * from, AbsColleagus * to)
	{
		to->Receive(from->GetData());
	}
};

/*老板同事类*/
class Boss : public AbsColleagus
{
public:
	void Receive(char * info)
	{
		cout << "boss receiver " << info << endl;
	}
};

/*经理同事类*/
class Manager : public AbsColleagus
{
public:
	Manager()
	{
		mediator = new CompanyMediator;
		boss = new Boss;
	}
	~Manager()
	{
		delete mediator;
		delete boss;
		mediator = NULL;
		boss = NULL;
	}
	void Receive(char * info)
	{
		cout << "manager receiver " << info << endl;
	}
	void SendToBoss()
	{
		mediator->SendMssageTo(this, boss);
	}
private:
	AbsMediator * mediator;
	AbsColleagus * boss;
};


int main()
{
	Boss * boss = new Boss;
	Manager * manager = new Manager;
	manager->SetData("hello boss");
	manager->SendToBoss();
	
	delete boss;
	delete manager;
	return 0;
}
