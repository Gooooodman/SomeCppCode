#include <iostream>
/*
	����һ�����ڴ�������Ľӿ�,������������� 
	��һ����ʵ����,FactoryMethodʹһ�����ʵ����
	�ӳٵ������� 
*/
using namespace std;

/*�����Ʒ��*/
class AbsProduct
{
	
};

/*��Ʒʵ����*/
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

/*������Ʒ*/
class Creator
{
public:
	virtual AbsProduct * CreateProduct(int params) = 0;
};

/*��������ʵ��*/
/*��֪���������������*/
class ConCreator : public Creator
{
public:
	AbsProduct * product;
	/*���ݲ����������*/
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
