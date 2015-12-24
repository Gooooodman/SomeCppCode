#include <iostream>
/*
	Bridge-将抽象部分与它的实现部分分离,
	使它们都可以独立的变化 
*/
using namespace std;

/*定义Person实现类的接口*/
class PersonImpl
{
public:
	virtual void ImplWork() = 0;
	virtual void ImplSleep() = 0;
	virtual void ImplEat() = 0;
};

/*Person实现类可以有多种*/
class PersonImpleA : public PersonImpl
{
public:
	void ImplWork()
	{
		cout << "impl work" << endl;
	}
	void ImplSleep()
	{
		cout << "impl sleep" << endl;
	}
	void ImplEat()
	{
		cout << "eat apple" << endl;
	}
};

/*Person类的抽象接口*/
/*通过组合对象方式调用实现对象*/
class AbsPerson
{
public:
	AbsPerson(PersonImpl * person)
	{
		this->person = person;
	}
	virtual void Work()
	{
		person->ImplWork();
	}
	virtual void Sleep()
	{
		person->ImplSleep();
	}
	virtual void Eat()
	{
		person->ImplEat();
	}
	virtual void Show() = 0;
private:
	char * name;
	PersonImpl * person;
};

/*Person类的扩充接口*/
/*抽象部分与实现部分分离,可独立扩充接口*/
class Person : public AbsPerson
{
public:
	Person(PersonImpl *person) : AbsPerson(person){}
	virtual void Show()
	{
		Work();
		Sleep();
		Eat();
	}
//	virtual void Work(){}
//	virtual void Sleep(){}
//	virtual void Eat(){}
	virtual void talk(){}
};

int main()
{
	PersonImpl *personImpl = new PersonImpleA;
	AbsPerson *person = new Person(personImpl);
	person->Show();
	
	delete personImpl;
	delete person;
	return 0;
}
