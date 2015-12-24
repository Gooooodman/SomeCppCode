#include <iostream>
/*
	State-允许一个对象在其内部状态改变时改变它的
	行为,对象看起来似乎修改了它所属的类 
*/
using namespace std;

/*普通接口*/
class Context
{
public:
	static const int FORENOON_STATE = 0x00;
	static const int NOON_STATE = 0x01;
	static const int AFTERNOON_STATE = 0x02;
	virtual void Doing(int status) = 0;
};

/*状态抽象接口*/
class State
{
public:
	virtual void Handle(Context * context) = 0;
};

/*状态子类代表其中一种状态*/
class Forenoon : public State
{
public:
	void Handle(Context * context)
	{
		cout << "forenoon state" << endl;
	}
	/*使其成为单例*/
	static Forenoon * GetInstance()
	{
		if(forenoon == NULL)
		{
			forenoon = new Forenoon;
		}
		return forenoon;
	}
	static void Recyle()
	{
		if(forenoon != NULL)
		{
			delete forenoon;
			forenoon = NULL; 
		}
	}
private: 
	Forenoon(){}
	static Forenoon * forenoon;
};

Forenoon * Forenoon::forenoon = 0;

/*状态子类代表其中一种状态*/
class Noon : public State
{
public:
	void Handle(Context * context)
	{
		cout << "noon state" << endl;
	}
	static Noon * GetInstance()
	{
		if(noon == NULL)
		{
			noon = new Noon;
		}
		return noon;
	}
	static void Recyle()
	{
		if(noon != NULL)
		{
			delete noon;
			noon = NULL; 
		}
	}
private:
	Noon(){}
	static Noon * noon;
};

Noon * Noon::noon = 0;

class Afternoon : public State
{
public:
	void Handle(Context * context)
	{
		cout << "afternoon state" << endl;
	}
	static Afternoon * GetInstance()
	{
		if(afternoon == NULL)
		{
			afternoon = new Afternoon;
		}
		return afternoon;
	}
	static void Recyle()
	{
		if(afternoon != NULL)
		{
			delete afternoon;
			afternoon = NULL; 
		}
	}
private:
	Afternoon(){}
	static Afternoon * afternoon;
};

Afternoon * Afternoon::afternoon = 0;

/*状态子类代表其中一种状态*/
class Person : public Context
{
public:
	void Doing(int status)
	{
		Forenoon::Recyle();
		Noon::Recyle();
		Afternoon::Recyle();
		switch(status)
		{
		case FORENOON_STATE:
			state = Forenoon::GetInstance();
			break;
		case NOON_STATE:
			state = Noon::GetInstance();
			break;
		case AFTERNOON_STATE:
			state = Afternoon::GetInstance();
			break;
		}
		state->Handle(this);
	}
private:
	State * state;
};

int main()
{
	Person * person = new Person;
	person->Doing(Context::FORENOON_STATE); 
	person->Doing(Context::NOON_STATE); 
	person->Doing(Context::AFTERNOON_STATE); 
	
	delete person;
	return 0;
}
