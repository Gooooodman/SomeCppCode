#include <iostream>
/*
	Singleton-保证一个类仅有一个实例,
	并提供一个访问它的全局访问点 
*/
using namespace std;

/*单例类*/
class Singleton
{
public:	
	static Singleton * GetInstance()
	{
		/*只允许有一个实例*/
		/*在多线程语言中需要保证线程安全*/
		if(_Instance == 0)
		{
			_Instance = new Singleton;
		}
		return _Instance;
	}
protected:
	/*将构造私有化*/
	Singleton()
	{
		cout << "create instace" << endl;
	}
private:
	/*存储自身的静态实例*/
	static Singleton * _Instance;
};

Singleton * Singleton::_Instance = 0;

int main()
{
	Singleton * instance = Singleton::GetInstance();
	delete instance;
	return 0;
} 
