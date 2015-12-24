#include <iostream>
/*
	AbstractFactory-�ṩһ������һϵ����ػ��໥��������Ľӿ�,
	������ָ�����Ǿ������ 
*/
using namespace std;

/*�����Ʒϵ��*/
class AbsProduct
{
public:
	virtual void DoSomeThing() = 0;
};

/*A��Ʒϵ��ʵ��*/
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

/*B��Ʒϵ��ʵ��*/
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
	��������ӿ� 
	���������������ϵ�еĲ�Ʒ����	
*/
class AbsFactory
{
public:
	virtual AbsProduct* CreateProduct(int flag) = 0;
};

/*���ù�������ʵ��Ҳ����ԭ��*/
/*������ƷAϵ��ʵ����ʵ�ֹ���*/
class ProductAFactory : public AbsFactory
{
public:
	AbsProduct *CreateProduct(int flag)
	{
		/*���ݲ���������Ӧ�Ĳ�Ʒʵ��*/
		if(flag == 0)
		{
			absProduct = new ProductA;
		}
		/*��������...*/
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

/*������ƷBϵ��ʵ����ʵ�ֹ���*/
class ProductBFactory : public AbsFactory
{
public:
	AbsProduct *CreateProduct(int flag)
	{
		/*���ݲ���������Ӧ�Ĳ�Ʒʵ��*/
		if(flag == 0)
		{
			absProduct = new ProductB;
		}
		/*��������...*/
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
	/*����һ��Ϊ����*/
	static AbsFactory * factory;
	AbsProduct *absProduct;
};

AbsFactory * ProductBFactory::factory = 0;

/*��ϵͳ��Ҫ�ɶ��ϵ�в�Ʒ������*/
int main()
{
	/*ѡ��ʵ�ֲ�Ʒ��������*/
	AbsFactory * factory = ProductAFactory::GetInstance();
	/*factory = ProductBFactory::GetInstance()*/
	/*ͨ��������ȡ��Ʒʵ��*/
	/*ֻ��ʾ��Ʒ�ӿڶ�����ʵ��*/
	AbsProduct * product = factory->CreateProduct(0);
	
	
	delete factory;
	delete product;
	return 0;
}
