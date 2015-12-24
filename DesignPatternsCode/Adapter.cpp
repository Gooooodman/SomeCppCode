#include <iostream>
/*
	Adapter-将一个类的接口转化成客户希望的另一个接口,
	Adapter使得原本由于接口不兼容而不能一起工作 
	的那些类可以一起工作,结构性对象模式不是对接口
	和实现进行组合,而是描述了如何对一些对象进行组合
	从而实现新功能的一些方法 
*/
using namespace std;

/*已存在的目标类需要被转换接口*/
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

/*适配器抽象接口*/
class AbsOpAdapter
{
public:
	virtual int GetIntSum(int a, int b) = 0;
	virtual int GetIntReduce(int a, int b) = 0;
	virtual int GetMyData() = 0;
};

/*目标类适配器*/
class OperatorAdapter : public OperatorAdaptee,public AbsOpAdapter
{
public:
	/*转换目标的接口使其匹配*/
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
		/*经过处理*/
		return GetData() + 1;
	}
};

/*对目标的对象适配器*/
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
	/*转换目标的接口使其匹配*/
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
		/*经过处理*/
		return oa->GetData() + 1;
	}
private:
	OperatorAdaptee *oa;
};

int main()
{
	/*其他类中调用代码*/
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
