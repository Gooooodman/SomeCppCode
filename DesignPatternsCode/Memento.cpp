#include <iostream>
/*
	Memento-�ڲ��ƻ���װ�Ե�ǰ����,������һ������
	���ڲ�״̬,���ڸö���֮�Ᵽ�����״̬.�����Ժ�
	�Ϳɽ��ö���ָ���ԭ�ȱ����״̬ 
*/
using namespace std;

/*��ϢԴ����ӿ�*/
class Originator
{ 
public:
	virtual void Save() = 0;
	virtual void Restore() = 0;
};

/*����¼����ӿ�*/
template<class T> class Memento
{
public:
	virtual void ReadState(T * t) = 0;
	virtual void SaveState(T * t) = 0;
};

/*��ϢԴʵ��*/ 
class ConOriginator : Originator
{
public:
	void SetMemento(Memento<ConOriginator> * memento)
	{
		this->memento = memento;
	}
	void Save()
	{
		memento->SaveState(this);
	}
	void Restore()
	{
		memento->ReadState(this);
	}
	friend class OMemento;
private:
	int numstate;
	bool boolstate;
	Memento<ConOriginator> * memento;
};

class Data
{
public:
	int numstate;
	bool boolstate;
};

/*����¼ʵ��*/
class OMemento : public Memento<ConOriginator>
{
public:
	OMemento()
	{
		data = new Data;
	}
	~OMemento()
	{
		delete data;
		data = NULL;
	}
	void ReadState(ConOriginator * originator)
	{
		data->numstate = originator->numstate;
		data->boolstate = originator->boolstate;
	}
	void SaveState(ConOriginator * originator)
	{
		originator->numstate = data->numstate;
		originator->boolstate =	data->boolstate;
	}
private:
	Data * data;
};

int main()
{
	Memento<ConOriginator> * memento = new OMemento;
	ConOriginator * originator = new ConOriginator;
	originator->SetMemento(memento);
	originator->Save(); 
	originator->Restore();
	
	delete memento;
	delete originator;
	return 0;
}
