#include <iostream>
/*
	Mediator-��һ����������װһϵ�еĶ��󽻻�.
	�н���ʹ��������Ҫ��ʽ���໥����,�Ӷ�ʹ��
	�����ɢ,���ҿ��Զ����ĸı�����֮��Ľ���
*/
using namespace std;

/*ͬ�³���ӿ�*/
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

/*��Ϣ�н��߳���ӿ�*/
class AbsMediator
{
public:
	virtual void SendMssageTo(AbsColleagus * from, AbsColleagus * to) = 0;
};

/*��˾�н���ʵ��*/
class CompanyMediator : public AbsMediator
{
public:
	/*ʵ������ͨ��*/
	void SendMssageTo(AbsColleagus * from, AbsColleagus * to)
	{
		to->Receive(from->GetData());
	}
};

/*�ϰ�ͬ����*/
class Boss : public AbsColleagus
{
public:
	void Receive(char * info)
	{
		cout << "boss receiver " << info << endl;
	}
};

/*����ͬ����*/
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
