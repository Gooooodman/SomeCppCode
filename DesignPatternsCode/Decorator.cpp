#include <iostream>
/*
	Decorator-��̬�ظ��������һЩ�����ְ��.������ 
	������˵,Decorator������������Ϊ��� 
*/
using namespace std;

/*��ʾ��-PoolComputer�����*/
class Display
{
public:
	void Show()
	{
		cout << "display show!" << endl;
	} 
};

/*����-����ӵ����*/
class KeyBoard
{
public:
	void Press()
	{
		cout << "press KkeyBoard!" << endl;
	}		
};

/*���-����ӵ����*/
class Mouse
{
public:
	void Click()
	{
		cout << "click Mouse!" << endl;
	}		
};

/*�ɵ���-��Ҫ����װ��Ŀ����*/
/*�����ܲ������෽ʽ������ʱ*/
class PoolComputer
{
public:
	PoolComputer()
	{
		display = new Display;
	}
	~PoolComputer()
	{
		delete display;
	}
	void Start()
	{
		cout << "start..." << endl;	
	}
	void End()
	{
		cout << "shut down..." << endl;
	}
	void Show()
	{
		display->Show();
	}
private:
	Display * display;
};

/*��װ����*/
class AbsComputerWrap
{
public:
	virtual void Control() = 0;
};

/*��װ���һ��ʵ����*/
class NewComputerWrap : public AbsComputerWrap
{
public:
	NewComputerWrap()
	{
		keyboard = new KeyBoard;
		mouse = new Mouse;
		poolcomputer = new PoolComputer;
	}
	~NewComputerWrap()
	{
		delete keyboard;
		delete mouse;
		delete poolcomputer;
	}
	/*�ṩ�¹���*/
	void Control()
	{
		cout << "control" << endl;
		keyboard->Press();
		mouse->Click();
	}
	void Start()
	{
		poolcomputer->Start();
	}
	void End()
	{
		poolcomputer->End();
	}
	void Show()
	{
		poolcomputer->Show();
	}
private:
	KeyBoard * keyboard;
	Mouse * mouse;
	PoolComputer * poolcomputer;
};

int main()
{
	NewComputerWrap * ncw = new NewComputerWrap;
	ncw->Start();
	ncw->Control();
	ncw->Show();
	ncw->End();
	
	delete ncw;
	return 0;
}
