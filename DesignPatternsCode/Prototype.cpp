#include <iostream>
#include <cstring>
/*
	��ԭ��ʵ��ָ���������������,
	����ͨ���������ԭ���������µĶ��� 
*/
using namespace std;
/*����ԭ��*/
class AbsPrototype
{
public:
	/*������¡�������*/
	virtual AbsPrototype * Clone() = 0;
	virtual void ShowData() = 0;
	virtual void setData(char * data) = 0;
};

/*ԭ��ʵ����*/
class ConPrototype : public AbsPrototype
{
public:
	ConPrototype()
	{
		/*���ӵĹ����߼�*/
		data = new char(5);
	}
	/*�������캯��*/
	ConPrototype(ConPrototype * c)
	{
		this->data = c->data;
	}
	/*�ṩ��¡����*/
	AbsPrototype * Clone()
	{
		return new ConPrototype(this);
	}
	/*�ı�ֵ�������¶���*/
	void setData(char * data)
	{
		this->data = data;
	}
	void ShowData()
	{
		cout << data << endl;
	}
	~ConPrototype()
	{
		delete data;
	}
private:
	char * data;
};

int main()
{
	AbsPrototype * prototype = new ConPrototype;
	AbsPrototype * copy = prototype->Clone();
	
	prototype->setData("data");
	copy->setData("copy");
	
	prototype->ShowData();
	copy->ShowData();
	
	delete prototype;
	delete copy;
	return 0;
}
