#include <iostream>
/*
	Memento-在不破坏封装性的前提下,捕获下一个对象
	的内部状态,并在该对象之外保存这个状态.这样以后
	就可将该对象恢复到原先保存的状态 
*/
using namespace std;

/*信息源抽象接口*/
class Originator
{ 
public:
	virtual void Save() = 0;
	virtual void Restore() = 0;
};

/*备忘录抽象接口*/
template<class T> class Memento
{
public:
	virtual void ReadState(T * t) = 0;
	virtual void SaveState(T * t) = 0;
};

/*信息源实现*/ 
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

/*备忘录实现*/
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
