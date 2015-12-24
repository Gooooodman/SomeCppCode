#include <iostream>
/*
	Proxy-为其他对象提供一种代理以控制这个对象的访问
*/
using namespace std;

/*需要被代理的目标Conctrol类*/
class Control
{
public:
	virtual void ChangeData(char * data)
	{
		this->data = data;
	}
	virtual void ShowData()
	{
		cout << data << endl;
	}
private:
	char * data;
};

/*保护代理抽象接口*/
class ProtectProxy
{
public:
	virtual bool Check(int code) = 0;
}; 

/*虚代理抽象接口*/
class VirtualProxy
{
	/*...*/
};

/*远程代理抽象接口*/
class RemoteProxy
{
	/*...*/
};

/*代理实现类*/
class ControlProxy : public ProtectProxy, public Control
{
public:
	ControlProxy(int code)
	{
		this->code = code;
		control = new Control;
	}
	~ControlProxy()
	{
		delete control;
		control = NULL;
	}
	void ChangeData(char * data)
	{
		/*在调用目标之前检查*/
		if(Check(code))
		{
			control->ChangeData(data);
		}
		else
		{
			cout << "check failed!" << endl;
		}
	}
	void ShowData()
	{
		control->ShowData();
	}
private:
	Control * control;
	int code;
	bool Check(int code)
	{
		switch(code)
		{
		case 0:return false;
			break;
		case 1:return true;
			break;
		default:return false;
		}
	}
};

int main()
{
	ControlProxy * proxy = new ControlProxy(1);
	proxy->ChangeData("data");
	proxy->ShowData();
	
	delete proxy;
	return 0;
}

