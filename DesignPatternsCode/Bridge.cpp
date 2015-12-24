#include <iostream>
/*
	Bridge-�����󲿷�������ʵ�ֲ��ַ���,
	ʹ���Ƕ����Զ����ı仯 
*/
using namespace std;

/*����Personʵ����Ľӿ�*/
class PersonImpl
{
public:
	virtual void ImplWork() = 0;
	virtual void ImplSleep() = 0;
	virtual void ImplEat() = 0;
};

/*Personʵ��������ж���*/
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

/*Person��ĳ���ӿ�*/
/*ͨ����϶���ʽ����ʵ�ֶ���*/
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

/*Person�������ӿ�*/
/*���󲿷���ʵ�ֲ��ַ���,�ɶ�������ӿ�*/
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
