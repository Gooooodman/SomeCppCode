#include <iostream>
/*
	Command-��һ�������װΪһ������,�Ӷ�ʹ��
	���ò�ͬ������Կͻ����в�����,�������Ŷ�
	���¼������־,�Լ�֧�ֿ�ȡ���Ĳ���
*/
using namespace std;

/*�������ӿ�*/
class AbsTransaction
{
public:
	/*����*/
	virtual void Revoke() = 0;
	/*�ύһϵ�в���,��֤����ԭ����*/
	virtual void Commit() = 0;	
};

/*�洢*/
class SimpleFile
{
public:
	void Save(char * data)
	{
		cout << "save" << data << endl;
	}
};

/*����ʵ����-�洢����*/
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
