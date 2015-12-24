#include <iostream>
/*
	Decorator-动态地给对象添加一些额外的职责.就增加 
	功能来说,Decorator相比生成子类更为灵活 
*/
using namespace std;

/*显示器-PoolComputer的组件*/
class Display
{
public:
	void Show()
	{
		cout << "display show!" << endl;
	} 
};

/*键盘-新添加的组件*/
class KeyBoard
{
public:
	void Press()
	{
		cout << "press KkeyBoard!" << endl;
	}		
};

/*鼠标-新添加的组件*/
class Mouse
{
public:
	void Click()
	{
		cout << "click Mouse!" << endl;
	}		
};

/*旧电脑-需要被包装的目标类*/
/*当不能采用子类方式扩充类时*/
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

/*包装抽象*/
class AbsComputerWrap
{
public:
	virtual void Control() = 0;
};

/*包装类的一个实现类*/
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
	/*提供新功能*/
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
