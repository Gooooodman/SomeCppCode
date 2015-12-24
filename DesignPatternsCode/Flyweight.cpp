#include <iostream>
/*
	Flyweight-运用共享技术有效支持大量细粒度对象 
*/
using namespace std;

/*共享对象抽象接口*/
class AbsFlyweight
{
public:
	/*需要提供外部状态*/
	virtual void Operation(int state) = 0;
};

/*字符共享对象*/
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
	/*其他属性...*/
};

/*工厂生产字符享元对象*/
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
	/*实现工厂单例*/
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

/*包装含有坐标的享元对象*/
/*坐标作为享元对象的外部状态,而享元对象为内部状态*/
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

/*空间上的节省抵消了使用享元时,计算外部状态所需的时间开销*/
int main()
{
	CharFlyweightFactory * factory = CharFlyweightFactory::GetInstance();
	/*通过工厂创建两种不同类型的享元*/
	AbsFlyweight * englishfont = factory->CreateCharFlyweighth(CharFlyweightFactory::ENGLIST_TYPE);
	AbsFlyweight * chinesefont = factory->CreateCharFlyweighth(CharFlyweightFactory::CHINESE_TYPE);
	CharXyWrap * fontarray[30];
	/*需要创建大量对象*/
	for(int i = 0; i < 30; i++)
	{
		if(i < 20)
		{
			/*共同持有一个享元的引用*/
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
