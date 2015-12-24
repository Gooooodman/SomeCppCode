#include <iostream>
/*
	定义一个用于创建对象的接口,让子类决定创建 
	哪一个类实例化,FactoryMethod使一个类的实例化
	延迟到其子类 
*/
using namespace std;

/*抽象产品类*/
class AbsProduct
{
	
};

/*产品实现类*/
class ConcreateProduct : public AbsProduct
{
public:
	ConcreateProduct(char * name)
	{
		this->name = name;
		cout << "I'm prouct" << endl;
	}
private:
	char *name;
};

/*生产产品*/
class Creator
{
public:
	virtual AbsProduct * CreateProduct(int params) = 0;
};

/*工厂方法实现*/
/*不知道所需的子类类型*/
class ConCreator : public Creator
{
public:
	AbsProduct * product;
	/*根据参数处理对象*/
	AbsProduct * CreateProduct(int params)
	{
		if(params == 0)
		{
			/**/
		}
		product = new ConcreateProduct("product");
		return product;
	}	
};

int main()
{
	Creator * creator = new ConCreator;
	AbsProduct * product = creator->CreateProduct(0);
	delete creator;
	
	delete product;
	return 0;
}
