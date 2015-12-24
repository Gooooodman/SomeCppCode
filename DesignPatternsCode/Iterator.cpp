#include <iostream>
/*
	提供一种方法顺序访问一个聚合对象中的
	各个元素,而又不暴露该对象的内部表示 
*/
using namespace std;

/*提供数据结构的类*/
class SimpleArray
{
public:	
	SimpleArray()
	{
		length = 10;
		array = new int(length);
		for(int i = 0; i < length; i++)
		{
			* (array + i) = i;
		}
	}
	int * GetArray()
	{
		return array;
	}
	int  GetLength()
	{
		return length;
	}
	~SimpleArray()
	{
		delete array;
		array = NULL;
	}
private:
	int * array;
	int length;
};

/*外部迭代器抽象接口*/
template<class T> class OutIterator
{
public:
	virtual T First() = 0;
	virtual T Next() = 0;
	virtual bool IsDone() = 0;
	virtual T CurrentItem() = 0;
};

/*外部迭代器实现*/
class ArrayOutInterator : public OutIterator<int>
{
public:
	ArrayOutInterator()
	{
		position = 0;
	}
	void SetArray(SimpleArray * array)
	{
		this->array = array->GetArray();
		this->length = array->GetLength();
	}
	int First()
	{
		return * array;
	}
	int Next()
	{
		if(!IsDone())
		{
			position++;
			return * (array + position);
		}
	}
	bool IsDone()
	{
		if(position == length - 1)
		{
			return true;
		}
		return false;
	}
	int CurrentItem()
	{
		return position;
	}
private:
	int * array;
	int position;
	int length;
};

/*内部迭代器抽象接口*/
template<class T> class InIterator
{

};

/*内部迭代器实现*/
class ArrayInIterator : public InIterator<int>
{
public:
	void SetArray(SimpleArray * array)
	{
		this->array = array->GetArray();
		this->length = array->GetLength();
	}
	void SetCallBack(void (* OnType) (int data))
	{
		this->OnType = OnType;
	}
	void Traveersal()
	{
		for(int i = 0; i < length; i++)
		{
			if(OnType != NULL)
			{
				OnType(* (array + i));
			}
		}
	}
private:
	void (* OnType) (int data);
	int * array;
	int length;
};

void OnType(int data)
{
	cout << data << endl;
}

int main()
{
	SimpleArray * array = new SimpleArray;
	ArrayOutInterator * outinterator = new ArrayOutInterator;
	outinterator->SetArray(array);
	while(!outinterator->IsDone())
	{
		cout << outinterator->Next() << endl;
	}
	
	ArrayInIterator * initerator = new ArrayInIterator;
	initerator->SetArray(array);
	initerator->SetCallBack(OnType);
	initerator->Traveersal();
	
	delete outinterator;
	delete initerator;
	delete array;
	return 0;
}
