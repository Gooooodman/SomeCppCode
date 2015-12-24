#include <iostream>
/*
	Adapter-��һ����Ľӿ�ת���ɿͻ�ϣ������һ���ӿ�,
	Adapterʹ��ԭ�����ڽӿڲ����ݶ�����һ���� 
	����Щ�����һ����,�ṹ�Զ���ģʽ���ǶԽӿ�
	��ʵ�ֽ������,������������ζ�һЩ����������
	�Ӷ�ʵ���¹��ܵ�һЩ���� 
*/
using namespace std;

/*�Ѵ��ڵ�Ŀ������Ҫ��ת���ӿ�*/
class OperatorAdaptee
{
public:
	 virtual float GetSum(float a, float b,float c)
	 {
	 	return a + b + c;
	 }
	 virtual float GetReduce(float a, float b)
	 {
	 	return a - b;
	 }
	 virtual float GetData()
	 {
	 	return 1.23;	
	 }
};

/*����������ӿ�*/
class AbsOpAdapter
{
public:
	virtual int GetIntSum(int a, int b) = 0;
	virtual int GetIntReduce(int a, int b) = 0;
	virtual int GetMyData() = 0;
};

/*Ŀ����������*/
class OperatorAdapter : public OperatorAdaptee,public AbsOpAdapter
{
public:
	/*ת��Ŀ��Ľӿ�ʹ��ƥ��*/
	int GetIntSum(int a, int b)
	{
		return (int) GetSum((float) a, (float) b, (float)0);
	}
	int GetIntReduce(int a, int b)
	{
		return (int) GetReduce((float) a, (float) b);
	}
	int GetMyData()
	{
		/*��������*/
		return GetData() + 1;
	}
};

/*��Ŀ��Ķ���������*/
class ObjectOpAdapter : public AbsOpAdapter
{
public:
	ObjectOpAdapter()
	{
		oa = new OperatorAdaptee;
	}
	~ObjectOpAdapter()
	{
		delete oa;
	}
	/*ת��Ŀ��Ľӿ�ʹ��ƥ��*/
	int GetIntSum(int a, int b)
	{
		return (int) oa->GetSum((float) a, (float) b, (float)0);
	}
	int GetIntReduce(int a, int b)
	{
		return (int) oa->GetReduce((float) a, (float) b);
	}
	int GetMyData()
	{
		/*��������*/
		return oa->GetData() + 1;
	}
private:
	OperatorAdaptee *oa;
};

int main()
{
	/*�������е��ô���*/
	OperatorAdapter * adapter = new OperatorAdapter;
	cout << "1 + 5 = " << adapter->GetIntSum(1, 5) << endl;
	cout << "5 - 2 = " << adapter->GetIntReduce(5, 2) << endl;
	
	ObjectOpAdapter * ooadapter = new ObjectOpAdapter;
	cout << "1 + 4 = " << adapter->GetIntSum(1, 4) << endl;
	cout << "8 - 2 = " << adapter->GetIntReduce(8, 2) << endl;
	
	delete adapter;
	delete ooadapter;
	return 0;
}
