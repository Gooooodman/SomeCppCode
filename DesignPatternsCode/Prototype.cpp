#include <iostream>
#include <cstring>
/*
	用原型实例指定创建对象的种类,
	并且通过拷贝这个原型来创建新的对象 
*/
using namespace std;
/*抽象原型*/
class AbsPrototype
{
public:
	/*声明克隆自身操作*/
	virtual AbsPrototype * Clone() = 0;
	virtual void ShowData() = 0;
	virtual void setData(char * data) = 0;
};

/*原型实现类*/
class ConPrototype : public AbsPrototype
{
public:
	ConPrototype()
	{
		/*复杂的构造逻辑*/
		data = new char(5);
	}
	/*拷贝构造函数*/
	ConPrototype(ConPrototype * c)
	{
		this->data = c->data;
	}
	/*提供克隆函数*/
	AbsPrototype * Clone()
	{
		return new ConPrototype(this);
	}
	/*改变值以生成新对象*/
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
