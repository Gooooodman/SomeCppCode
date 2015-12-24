#include <iostream>

/*
	Strategy-定义一系列的算法,把它们一个个封装起来,
	 并且使它们可相互替换,本模式使得算法的变化可独
	 立于它们的客户 
*/

using namespace std;

/*
	收费类型枚举 
*/
enum
{
	Normal,Rebate
};

/*
	收费公共接口 
*/
class CashSuper
{
public:
	virtual double AcceptCash(double money) = 0;
};

/*
	正常收费子类 
*/
class CashNormal: public CashSuper
{
public:
	double AcceptCash(double money)
	{
		return money;
	}
};

/*
	打折收费子类 
*/
class CashRebate: public CashSuper
{
public:
	CashRebate(){}
	CashRebate(double rebate)
	{
		moneyRebate = rebate;
	}
	double AcceptCash(double money)
	{
		return money * moneyRebate;
	}
private:
	double moneyRebate;	
};

/*
	收费上下文 
*/
class CashContext
{
	
public:
	CashContext(int type)
	{
		switch(type)
		{
		case Normal:
			cs = new CashNormal();
			break;
		case Rebate:
			cs = new CashRebate(0.6);
			break;
		}
	}
	double getResult(double money)
	{
		return cs->AcceptCash(money);
	}
private:
	CashSuper *cs = NULL;
};

//class CashFactory
//{
//public:
//	static CashSuper *createCashAccept(int type)
//	{
//		CashSuper *cs = NULL;
//		switch(type)
//		{
//		case Normal:
//			cs = new CashNormal();
//			break;
//		case Rebate:
//			cs = new CashRebate(0.6);
//			break;
//		}
//		return cs;
//	}
//};
	
int main()
{
	CashContext * cc = new CashContext(Normal);
	cout<< "money-->"<< cc->getResult(100);
	
	delete cc;
	return 0;
}
