#include <iostream>
/*
	表示一个作用对象结构中的各元素的操作,它使
	你可以在不改变各元素的前提下定义作用于这
	些元素的新操作 
*/
using namespace std;

class View;
class ViewGroup;
/*访问者抽象接口*/
class AbsVisitor
{
public:
	virtual void VisitView(View * view) = 0;
	virtual void VisitViewGroup(ViewGroup * viewgroup) = 0;
};

/*被访问者抽象接口*/
class Element
{
public:
	virtual void Accept(AbsVisitor * visitor) = 0;
};

/*Abs抽象接口继承被访问者抽象接口*/
class AbsView : public Element
{
public:
	virtual void Measure() = 0;
	virtual void Layout() = 0;
	virtual void Draw() = 0;
};

/*view被访问者*/
class View : public AbsView
{
public:
	void Measure()
	{
		cout << "view mesure..." << endl;
	}
	void Layout()
	{
		return;
	}
	void Draw()
	{
		cout << "view draw..." << endl;
	}
	void Accept(AbsVisitor * visitor)
	{
		/*负责自身被访问规则*/
		visitor->VisitView(this);
	}
};

/*ViewGroup被访问者*/
class ViewGroup : public AbsView
{
public:
	void Measure()
	{
		cout << "viewgroup mesure..." << endl;
	}
	void Layout()
	{
		cout << "viewgroup layout..." << endl;
	}
	void Draw()
	{
		cout << "viewgroup draw..." << endl;
	}
	virtual void Accept(AbsVisitor * visitor)
	{
		/*负责自身被访问规则*/
		visitor->VisitViewGroup(this);
	}
};

/*View访问者实现*/
class ViewVisister : public AbsVisitor
{
public:
	void VisitView(View * view)
	{
		view->Measure();
		view->Draw();
	}
	void VisitViewGroup(ViewGroup * viewgroup)
	{
		viewgroup->Measure();
		viewgroup->Layout();
		viewgroup->Draw();
	}
};

/*总调用者-被访问者实现*/
class CustomView : public ViewGroup
{
public:
	CustomView()
	{
		viewgroup = new ViewGroup;
		view = new View;
	}
	~CustomView()
	{
		delete viewgroup;
		viewgroup = NULL;
		delete view;
		view = NULL;
	}
	void Accept(AbsVisitor * visitor)
	{
		/*单独访问子元素*/
		viewgroup->Accept(visitor);
		view->Accept(visitor);
	}
private:
	ViewGroup * viewgroup;
	View * view;
};

int main()
{
	ViewVisister * visitor = new ViewVisister;
	CustomView * v = new CustomView;
	v->Accept(visitor);
	
	delete visitor;
	delete v;
	return 0;
}
