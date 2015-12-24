#include <iostream>
/*
	Oserver-���������һ�Զ��������ϵ,
	�Ա㵱һ�������״̬�����ı�ʱ,��������
	���Ķ��󶼵õ�֪ͨ���Զ�ˢ�� 
*/
using namespace std;

/*�۲��߳���ӿ�*/ 
template<class T> class AbsObserver
{
public:
	/*����*/
	virtual void Update(T * info) = 0;
};

/*�۲�Ŀ�����ӿ�*/
template<class T> class AbsSubject
{
public:
	/*��Ŀ��*/
	virtual void Regisiter(AbsObserver<char> * oserver) = 0;
	/*�����*/
	virtual void Unregisiter(AbsObserver<char> * oserver) = 0;
	/*֪ͨ�۲���*/
	virtual void NotifyAll(T * info) = 0; 
};

/*�۲�Ŀ��ʵ��*/
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
	/*��ȡ����*/
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

/*�۲���A*/
class ObserverA : public AbsObserver<char>
{
public:
	void Update(char * info)
	{
		cout << "ObserverA recever" << info << endl;
	}
};

/*�۲���B*/
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
