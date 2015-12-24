#include <iostream>
/*
	Flyweight-���ù�������Ч֧�ִ���ϸ���ȶ��� 
*/
using namespace std;

/*����������ӿ�*/
class AbsFlyweight
{
public:
	/*��Ҫ�ṩ�ⲿ״̬*/
	virtual void Operation(int state) = 0;
};

/*�ַ��������*/
class CharFlyweight : public AbsFlyweight
{
public:
	void Operation(int state)
	{
		if(state == 0){/*...*/}
	}
	CharFlyweight(int size, char * color, char * style, char * format)
	{
		this->size = size;
		this->color = color;
		this->style = style;
		this->format = format;
	}
	int size;
	char * color;
	char * style;
	char * format;
	/*��������...*/
};

/*���������ַ���Ԫ����*/
class CharFlyweightFactory
{
public:
	static const int ENGLIST_TYPE = 0;
	static const int CHINESE_TYPE = 1;
	AbsFlyweight * CreateCharFlyweighth(int type)
	{
		AbsFlyweight * charweight;
		switch(type)
		{
		case ENGLIST_TYPE:
			charweight = new CharFlyweight(4, "0x123456", "en", "center");
			break;
		case CHINESE_TYPE:
			charweight = new CharFlyweight(3, "0x111222", "zh", "center");
			break;
		default:cout << "failed" << endl;
			break;
		}
		return charweight;
	}
	/*ʵ�ֹ�������*/
	static CharFlyweightFactory * GetInstance()
	{
		if(factory == 0)
		{
			factory = new CharFlyweightFactory;
		}
		return factory;
	}
private:
	CharFlyweightFactory(){}
	static CharFlyweightFactory * factory;
};

CharFlyweightFactory * CharFlyweightFactory::factory = 0;

/*��װ�����������Ԫ����*/
/*������Ϊ��Ԫ������ⲿ״̬,����Ԫ����Ϊ�ڲ�״̬*/
class CharXyWrap
{
public:
	CharXyWrap(CharFlyweight * font, int x , int y)
	{
		this->font = font;
		this->x = x;
		this->y = y;
	}
	void Draw()
	{
		cout << font->style << "draw " << x << ',' << y << endl;
		/*...*/
	}
private:
	int x;
	int y;
	CharFlyweight * font;	
};

/*�ռ��ϵĽ�ʡ������ʹ����Ԫʱ,�����ⲿ״̬�����ʱ�俪��*/
int main()
{
	CharFlyweightFactory * factory = CharFlyweightFactory::GetInstance();
	/*ͨ�������������ֲ�ͬ���͵���Ԫ*/
	AbsFlyweight * englishfont = factory->CreateCharFlyweighth(CharFlyweightFactory::ENGLIST_TYPE);
	AbsFlyweight * chinesefont = factory->CreateCharFlyweighth(CharFlyweightFactory::CHINESE_TYPE);
	CharXyWrap * fontarray[30];
	/*��Ҫ������������*/
	for(int i = 0; i < 30; i++)
	{
		if(i < 20)
		{
			/*��ͬ����һ����Ԫ������*/
			fontarray[i] = new CharXyWrap((CharFlyweight *)englishfont, 1, 5);
		}
		else
		{
			fontarray[i] = new CharXyWrap((CharFlyweight *)chinesefont, 8, 4);
		}
		fontarray[i]->Draw();
	}
	
	delete factory;
	for(int i = 0; i < 30; i++)
	{
		delete fontarray[i];
		fontarray[i] = NULL;
	}
	return 0;
} 
