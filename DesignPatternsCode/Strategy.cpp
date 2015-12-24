#include <iostream>

/*
	Strategy-����һϵ�е��㷨,������һ������װ����,
	 ����ʹ���ǿ��໥�滻,��ģʽʹ���㷨�ı仯�ɶ�
	 �������ǵĿͻ� 
*/

using namespace std;

/*
	�շ�����ö�� 
*/
enum
{
	Normal,Rebate
};

/*
	�շѹ����ӿ� 
*/
class CashSuper
{
public:
	virtual double AcceptCash(double money) = 0;
};

/*
	�����շ����� 
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
	�����շ����� 
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
	�շ������� 
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
