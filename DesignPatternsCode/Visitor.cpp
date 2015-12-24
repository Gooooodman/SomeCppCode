#include <iostream>
/*
	��ʾһ�����ö���ṹ�еĸ�Ԫ�صĲ���,��ʹ
	������ڲ��ı��Ԫ�ص�ǰ���¶�����������
	ЩԪ�ص��²��� 
*/
using namespace std;

class View;
class ViewGroup;
/*�����߳���ӿ�*/
class AbsVisitor
{
public:
	virtual void VisitView(View * view) = 0;
	virtual void VisitViewGroup(ViewGroup * viewgroup) = 0;
};

/*�������߳���ӿ�*/
class Element
{
public:
	virtual void Accept(AbsVisitor * visitor) = 0;
};

/*Abs����ӿڼ̳б������߳���ӿ�*/
class AbsView : public Element
{
public:
	virtual void Measure() = 0;
	virtual void Layout() = 0;
	virtual void Draw() = 0;
};

/*view��������*/
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
		/*�����������ʹ���*/
		visitor->VisitView(this);
	}
};

/*ViewGroup��������*/
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
		/*�����������ʹ���*/
		visitor->VisitViewGroup(this);
	}
};

/*View������ʵ��*/
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

/*�ܵ�����-��������ʵ��*/
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
		/*����������Ԫ��*/
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
