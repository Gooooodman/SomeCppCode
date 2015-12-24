#include <iostream>
/*
	Command-将一个请求封装为一个对象,从而使你
	可用不同的请求对客户进行参数化,对请求排队
	或记录请求日志,以及支持可取消的操作
*/
using namespace std;

/*事务抽象接口*/
class AbsTransaction
{
public:
	/*撤销*/
	virtual void Revoke() = 0;
	/*提交一系列操作,保证操作原子性*/
	virtual void Commit() = 0;	
};

/*存储*/
class SimpleFile
{
public:
	void Save(char * data)
	{
		cout << "save" << data << endl;
	}
};

/*事务实现类-存储事务*/
class FileEditor : public AbsTransaction
{
public:
	void SetSimpleFile(SimpleFile * file)
	{
		this->file = file;
	}
	void Put(char * data)
	{
		this->data = data;
	}
	void Revoke()
	{
		data = NULL;
		cout << "revoke!" << endl;
	}
	void Commit()
	{
		file->Save(data);
	}
private:
	char * data;
	SimpleFile *file; 
};

int main()
{
	FileEditor * editor = new FileEditor; 
	SimpleFile * file = new SimpleFile;
	editor->SetSimpleFile(file);
	editor->Put("data");
//	editor->Revoke();
	editor->Commit();
	
	delete editor;
	delete file;
	return 0;
}
