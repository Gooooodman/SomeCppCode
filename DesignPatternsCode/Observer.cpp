#include <iostream>
/*
	Oserver-定义对象间的一对多的依赖关系,
	以便当一个对象的状态发生改变时,所有依赖
	它的对象都得到通知并自动刷新 
*/
using namespace std;

/*观察者抽象接口*/ 
template<class T> class AbsObserver
{
public:
	/*更新*/
	virtual void Update(T * info) = 0;
};

/*观察目标抽象接口*/
template<class T> class AbsSubject
{
public:
	/*绑定目标*/
	virtual void Regisiter(AbsObserver<char> * oserver) = 0;
	/*解除绑定*/
	virtual void Unregisiter(AbsObserver<char> * oserver) = 0;
	/*通知观察者*/
	virtual void NotifyAll(T * info) = 0; 
};

/*观察目标实现*/
class ConSunject : public AbsSubject<char>
{
public:
	void Doing()
	{
		cout << "doing..." << endl;
		NotifyAll("doing");
	}
	void Regisiter(AbsObserver<char> * observer)
	{
		int i;
		for(i = 0; i < MAX_OBSERVER; i++)
		{
			if(this->observer[i] == NULL)
			{
				this->observer[i] = observer;
				break;
			}
		}
		if(i == MAX_OBSERVER)
		{
			cout << "full!" << endl;
			return;
		}
	}
	void Unregisiter(AbsObserver<char> * observer)
	{
		int i;
		for(i = 0; i < MAX_OBSERVER; i++)
		{
			if(this->observer[i] == NULL)
			{
				break; 
			}
			else if(this->observer[i] == observer)
			{
				for(int j = i; j < MAX_OBSERVER - 1; j++)
				{
					this->observer[j] = this->observer[j + 1];
				}
				break;
			}
		}
		if(i == MAX_OBSERVER)
		{
			cout << "null!" << endl;
			return;
		}
	}
	void NotifyAll(char * info)
	{
		for(int i = 0; i < MAX_OBSERVER; i++)
		{
			if(observer[i] == NULL)
			{
				break;
			}
			observer[i]->Update(info);
		}
	}
	/*获取单例*/
	static ConSunject * GetInstance()
	{
		if(subject == NULL)
		{
			subject = new ConSunject;
		}
		return subject;
	}
private:
	ConSunject()
	{
		for(int i = 0; i < MAX_OBSERVER; i++)
		{
			observer[i] = NULL;
		}
	}
	static const int MAX_OBSERVER = 10;
	AbsObserver<char> * observer[MAX_OBSERVER];
	static ConSunject * subject;
};

ConSunject * ConSunject::subject = 0;

/*观察者A*/
class ObserverA : public AbsObserver<char>
{
public:
	void Update(char * info)
	{
		cout << "ObserverA recever" << info << endl;
	}
};

/*观察者B*/
class ObserverB : public AbsObserver<char>
{
public:
	void Update(char * info)
	{
		cout << "ObserverB recever" << info << endl;
	}
};

int main()
{
	ConSunject * subject = ConSunject::GetInstance();
	ObserverA * oa = new ObserverA;
	ObserverB * ob = new ObserverB;
	subject->Regisiter(oa);
	subject->Regisiter(ob);
	subject->Doing();
	subject->Unregisiter(oa);
	subject->Doing();
	
	delete subject;
	delete oa;
	delete ob;
	return 0;
}
