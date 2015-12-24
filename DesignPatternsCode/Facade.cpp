#include <iostream>
/*
	Facade-Ϊ��ϵͳ�е�һ��ӿ��ṩһ��һ�µĽ���,
	Facade������һ���߲�ӿ�,����ӿ�ʹ��һ��ϵͳ
	��������ʹ�� 
*/
using namespace std;

/*��ϵͳA*/
class SystemA
{
public:
	void SystemIn()
	{
		cout << "������SystemA" << endl;
	}
};

/*��ϵͳB*/
class SystemB
{
public:
	void SystemCenter()
	{
		cout << "������SystemBCenter" << endl;
	} 
};

/*��ϵͳC*/
class SystemC
{
public:
	void SystemCIn()
	{
		cout << "������SystemCCenter" << endl;
	} 
};

/*�������ϵͳ*/
/*���ͻ�������������ʵ���ϵͳ*/
class FacadeCenter
{
public:	
	FacadeCenter()
	{
		systemA = new SystemA;
		systemB = new SystemB;
		systemC = new SystemC;
	}
	void CheckUser()
	{
		cout << "check success!" << endl;
	}
	void SelectSystem()
	{
		/*ѡ��ϵͳ�߼�*/
		cout << "please select!" << endl;
		switch(0)
		{
		case 0:
			systemA->SystemIn();
			break;
		default:;
		}
	}
	~FacadeCenter()
	{
		delete systemA;
		delete systemB;
		delete systemC;
	}
private:
	SystemA * systemA;
	SystemB * systemB;
	SystemC * systemC;
};

int main()
{
	FacadeCenter * center = new FacadeCenter;
	center->SelectSystem();
	
	delete center;
	return 0;
}
