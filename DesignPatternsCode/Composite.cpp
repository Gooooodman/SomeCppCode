#include <iostream>
/*
	Composite-将对象组合成树型结构以表示"部分-整体"的
	层次结构.Composite使得用户对单个对象和 
	组合对象的使用具有一致性 
*/
using namespace std;

/*抽象View类*/
/*定义包含基本对象和组合对象的类层次结构*/
class AbsView
{
public:
	virtual void Add(AbsView * view) = 0;
	virtual void Remove(AbsView * view) = 0;
	virtual AbsView * Get(int i) = 0;
	virtual void Draw() = 0;
};

/*View实现类*/
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

/*ViewGroup组合View产生View树形结构*/
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
	/*其他子view*/
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
