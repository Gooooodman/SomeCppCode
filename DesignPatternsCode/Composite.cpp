#include <iostream>
/*
	Composite-��������ϳ����ͽṹ�Ա�ʾ"����-����"��
	��νṹ.Compositeʹ���û��Ե�������� 
	��϶����ʹ�þ���һ���� 
*/
using namespace std;

/*����View��*/
/*������������������϶�������νṹ*/
class AbsView
{
public:
	virtual void Add(AbsView * view) = 0;
	virtual void Remove(AbsView * view) = 0;
	virtual AbsView * Get(int i) = 0;
	virtual void Draw() = 0;
};

/*Viewʵ����*/
class View : public AbsView
{
	virtual void Draw()
	{
		cout << "View Draw" << endl;
	}
	virtual void Add(AbsView * view)
	{
		return;
	}
	virtual	void Remove(AbsView * view)
	{
		return;
	}
	virtual AbsView *Get(int i)
	{
		return NULL;
	}
};

/*ViewGroup���View����View���νṹ*/
class ViewGroup : public View
{
public:
	ViewGroup()
	{
		view = new View;	
	}
	virtual void Draw()
	{
		view->Draw();
	}
	virtual void Add(AbsView * view)
	{
		cout << "View Add" << endl;
	}
	virtual	void Remove(AbsView * view)
	{
		cout << "Remove" << endl;
		delete view;
		view = NULL;
	}
	virtual AbsView *Get(int i)
	{
		return view;
	}
private:
	AbsView * view;
	/*������view*/
};

int main()
{
	AbsView * viewGroup = new ViewGroup;
	viewGroup->Add(NULL);
	viewGroup->Draw();
	viewGroup->Remove(NULL);
	
	delete viewGroup;
	return 0;
}
