#include <iostream>
/*
	Builder-将一个复杂对象的构建与它的表示分离,
	使得同样的创建过程可以创建不同的表示 
*/
using namespace std;

/*计算机抽象接口*/
/*一般产品不存在抽象接口,通常此对象构成复杂,没有相似对象*/
class AbsComputer
{
public:
	virtual void show() = 0;
	virtual void setCPU(char * CPU) = 0;
	virtual void setGPU(char * GPU) = 0;
	virtual void setHost(char * Host) = 0;
	/*其他函数...*/
};

/*计算机实现类*/
/*复杂对象的表示与构建分离*/
class ComputerA : public AbsComputer
{
public:
	void setCPU(char * CPU)
	{
		this->CPU = CPU;
	}
	void setGPU(char * GPU)
	{
		this->GPU = GPU;
	}
	void setHost(char * Host)
	{
		this->Host = Host;
	}
	void show()
	{
		cout << "this computer:" << endl;
		cout << "cpu:" << CPU << endl;
		cout << "gpu:" << GPU << endl;
		cout << "host:" << Host << endl;
	}
private:
	/*一系列复杂构成...*/
	char * CPU;
	char * GPU;
	char * Host;
};

/*构建抽象接口*/
class AbsComputerBuilder
{
public:
	/*创建和构建对象过程*/
	virtual void setCPU(char * type) = 0;
	virtual void setGPU(char * type) = 0;
	virtual void setHost(char * type) = 0;
	virtual AbsComputer * Builder() = 0;
};

/*建造者实现*/
class ComputerBuilder : public AbsComputerBuilder
{
public:
	void setCPU(char * type)
	{
		this->ccpu = type;
	}
	void setGPU(char * type)
	{
		this->cgpu = type;
	}
	void setHost(char * type)
	{
		this->chost = type;
	}
	AbsComputer * Builder()
	{
		computer = new ComputerA;
		/*一些复杂的构成逻辑*/
		computer->setCPU(ccpu);
		computer->setGPU(cgpu);
		computer->setHost(chost);
		return computer;
	}
private:
	AbsComputer * computer;
	char * ccpu;
	char * cgpu;
	char * chost;
};

int main()
{
	char cpu[] = "i5";
	char gpu[] = "AMD R9_295x2";
	char host[] = "外星人";
	AbsComputerBuilder * builder = new ComputerBuilder;
	builder->setCPU(cpu);
	builder->setGPU(gpu);
	builder->setHost(host);
	AbsComputer * computer = builder->Builder();
	computer->show();
	
	delete builder;
	delete computer;
	return 0;
}
