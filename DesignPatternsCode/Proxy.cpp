#include <iostream>
/*
	Proxy-Ϊ���������ṩһ�ִ����Կ����������ķ���
*/
using namespace std;

/*��Ҫ�������Ŀ��Conctrol��*/
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

/*�����������ӿ�*/
class ProtectProxy
{
public:
	virtual bool Check(int code) = 0;
}; 

/*��������ӿ�*/
class VirtualProxy
{
	/*...*/
};

/*Զ�̴������ӿ�*/
class RemoteProxy
{
	/*...*/
};

/*����ʵ����*/
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
		/*�ڵ���Ŀ��֮ǰ���*/
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

