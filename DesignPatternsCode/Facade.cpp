#include <iostream>
/*
	Facade-为子系统中的一组接口提供一个一致的界面,
	Facade定义了一个高层接口,这个接口使这一子系统
	更加容易使用 
*/
using namespace std;

/*子系统A*/
class SystemA
{
public:
	void SystemIn()
	{
		cout << "进入了SystemA" << endl;
	}
};

/*子系统B*/
class SystemB
{
public:
	void SystemCenter()
	{
		cout << "进入了SystemBCenter" << endl;
	} 
};

/*子系统C*/
class SystemC
{
public:
	void SystemCIn()
	{
		cout << "进入了SystemCCenter" << endl;
	} 
};

/*外观中心系统*/
/*将客户的请求代理到合适的子系统*/
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
		/*选择系统逻辑*/
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
