#include <iostream>
/*
	Singleton-��֤һ�������һ��ʵ��,
	���ṩһ����������ȫ�ַ��ʵ� 
*/
using namespace std;

/*������*/
class Singleton
{
public:	
	static Singleton * GetInstance()
	{
		/*ֻ������һ��ʵ��*/
		/*�ڶ��߳���������Ҫ��֤�̰߳�ȫ*/
		if(_Instance == 0)
		{
			_Instance = new Singleton;
		}
		return _Instance;
	}
protected:
	/*������˽�л�*/
	Singleton()
	{
		cout << "create instace" << endl;
	}
private:
	/*�洢����ľ�̬ʵ��*/
	static Singleton * _Instance;
};

Singleton * Singleton::_Instance = 0;

int main()
{
	Singleton * instance = Singleton::GetInstance();
	delete instance;
	return 0;
} 
