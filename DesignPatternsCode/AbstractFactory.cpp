#include <iostream>
/*
	AbstractFactory-提供一个创建一系列相关或相互依赖对象的接口,
	而无需指定它们具体的类 
*/
using namespace std;

/*抽象产品系列*/
class AbsProduct
{
public:
	virtual void DoSomeThing() = 0;
};

/*A产品系列实现*/
class ProductA : public AbsProduct
{
public:
	ProductA()
	{
		cout << "product a" << endl;	
	}
	void DoSomeThing()
	{
		/*...*/
	}
};

/*B产品系列实现*/
class ProductB : public AbsProduct
{
public:
	ProductB()
	{
		cout << "product b" << endl;
	}
	void DoSomeThing()
	{
		/*...*/
	}
};

/*
	工厂抽象接口 
	用来抽象生产多个系列的产品工厂	
*/
class AbsFactory
{
public:
	virtual AbsProduct* CreateProduct(int flag) = 0;
};

/*常用工厂方法实现也可用原型*/
/*创建产品A系列实例的实现工厂*/
class ProductAFactory : public AbsFactory
{
public:
	AbsProduct *CreateProduct(int flag)
	{
		/*根据参数生成相应的产品实例*/
		if(flag == 0)
		{
			absProduct = new ProductA;
		}
		/*其他子类...*/
		return absProduct;
	}
	static AbsFactory * GetInstance()
	{
		if(factory == 0)
		{
			factory = new ProductAFactory;
		}
		return factory;
	}
private:
	static AbsFactory * factory;
	ProductAFactory(){}
	AbsProduct *absProduct;
};

AbsFactory * ProductAFactory::factory = 0;

/*创建产品B系列实例的实现工厂*/
class ProductBFactory : public AbsFactory
{
public:
	AbsProduct *CreateProduct(int flag)
	{
		/*根据参数生成相应的产品实例*/
		if(flag == 0)
		{
			absProduct = new ProductB;
		}
		/*其他子类...*/
		return absProduct;
	}
	static AbsFactory * GetInstance()
	{
		if(factory == 0)
		{
			factory = new ProductBFactory;
		}
		return factory;
	}
private:
	ProductBFactory(){}
	/*工厂一般为单例*/
	static AbsFactory * factory;
	AbsProduct *absProduct;
};

AbsFactory * ProductBFactory::factory = 0;

/*此系统需要由多个系列产品来配置*/
int main()
{
	/*选择实现产品创建工厂*/
	AbsFactory * factory = ProductAFactory::GetInstance();
	/*factory = ProductBFactory::GetInstance()*/
	/*通过参数获取产品实例*/
	/*只显示产品接口而不是实现*/
	AbsProduct * product = factory->CreateProduct(0);
	
	
	delete factory;
	delete product;
	return 0;
}
