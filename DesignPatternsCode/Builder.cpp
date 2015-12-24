#include <iostream>
/*
	Builder-��һ�����Ӷ���Ĺ��������ı�ʾ����,
	ʹ��ͬ���Ĵ������̿��Դ�����ͬ�ı�ʾ 
*/
using namespace std;

/*���������ӿ�*/
/*һ���Ʒ�����ڳ���ӿ�,ͨ���˶��󹹳ɸ���,û�����ƶ���*/
class AbsComputer
{
public:
	virtual void show() = 0;
	virtual void setCPU(char * CPU) = 0;
	virtual void setGPU(char * GPU) = 0;
	virtual void setHost(char * Host) = 0;
	/*��������...*/
};

/*�����ʵ����*/
/*���Ӷ���ı�ʾ�빹������*/
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
	/*һϵ�и��ӹ���...*/
	char * CPU;
	char * GPU;
	char * Host;
};

/*��������ӿ�*/
class AbsComputerBuilder
{
public:
	/*�����͹����������*/
	virtual void setCPU(char * type) = 0;
	virtual void setGPU(char * type) = 0;
	virtual void setHost(char * type) = 0;
	virtual AbsComputer * Builder() = 0;
};

/*������ʵ��*/
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
		/*һЩ���ӵĹ����߼�*/
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
	char host[] = "������";
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
