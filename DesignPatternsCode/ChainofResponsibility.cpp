#include <iostream>
/*
	ChainofResponsibility-ʹ��������л��ᴦ������,
	�Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ,����Щ
	��������һ����,���������������ݸ�����,ֱ����һ��
	��������Ϊֹ 
*/
using namespace std;

/*�¼�����ӿ�*/
/*ͨ��������ģʽʹ��*/
class AbsEvent
{
public:
	/*�����¼�����*/
	virtual bool OnEvent(int action) = 0;
};

/*Ա��*/
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

/*����*/
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

/*�ϰ�*/
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
		/*�ж��¼��Ƿ����¼�*/
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
