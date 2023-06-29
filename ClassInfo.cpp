#include "Structure.h"

using namespace std;
using namespace Structure;

ClassInfo::ClassInfo()
{
	BaseUri = ".\\";
	StudentList = make_shared<StudentInfo>();
	ofstream stuFile(BaseUri + StuUri);
	StudentList->SaveStudentInfo(stuFile);
	stuFile.close();
}

ClassInfo::ClassInfo(istream& _file)
{
	// 第一行为基地址(不支持空格)
	std::string str;
	_file >> str;
	BaseUri = str;
	// 第二行为学生列表所在位置(相对于基地址)
	_file >> str;
	StuUri = str;
	ifstream stuFile(BaseUri + StuUri);
	StudentList = make_shared<StudentInfo>(stuFile);
	stuFile.close();
	// 剩下各行为课程id+课程名称+课程学分
	int id, point;
	char* buffer = new char[sizeof(int) / sizeof(char)];
	while (!_file.eof() || !_file.fail())
	{
		_file >> id >> str >> point;
		ifstream classFile(BaseUri + Snippet.EncodeBase64(to_string(id)));
		auto classData = make_shared<ClassData>(id, str, point, classFile);
		classFile.close();
		Data.emplace(id, classData);
	}
}

void ClassInfo::JoinStudentInfo(StudentInfo* _studentInfo)
{
	StudentList = shared_ptr<StudentInfo>(_studentInfo);
}

void ClassInfo::ChangeBaseUri(string _newUri, bool _moveData)
{
	if (_moveData)
	{

	}
	else
	{
		BaseUri = _newUri;
	}
}

std::shared_ptr<ClassData> ClassInfo::GetClassData(int _id)
{
	return Data[_id];
}

void ClassInfo::UpdateClassData(ClassData& _data)
{
	auto d = Data.find(_data.ID);
	auto ptr = make_shared<ClassData>(_data);
	if (d == Data.end())
	{
		Data.emplace(_data.ID, ptr);
		_data.InitialUpdate();
		StudentList->UpdateClassData(ptr);
	}
	else
	{
		d->second->ScanUpdate(_data);
		StudentList->UpdateClassData(d->second);
	}
}

void ClassInfo::SaveClassInfo(ostream& _file, bool _textMode)
{
	ofstream classFile(BaseUri + StuUri);
	StudentList->SaveStudentInfo(classFile, _textMode);
	classFile.close();
	if (_textMode)
	{
		_file << BaseUri << endl;
		_file << StuUri << endl;
		for (auto i = Data.begin(); i != Data.end(); i++)
		{
			_file << i->first << ' '
				<< i->second->Name << ' '
				<< i->second->Point << endl;
			ofstream classFile(BaseUri + Snippet.EncodeBase64(to_string(i->second->ID)));
			i->second->SaveClassData(classFile, _textMode);
			classFile.close();
		}
	}
	else
	{
		_file << BaseUri << StuUri;
		for (auto i = Data.begin(); i != Data.end(); i++)
		{
			_file << i->first << i->second->Name << i->second->Point;
			ofstream classFile(BaseUri + Snippet.EncodeBase64(to_string(i->second->ID)));
			i->second->SaveClassData(classFile, _textMode);
			classFile.close();
		}
	}
}