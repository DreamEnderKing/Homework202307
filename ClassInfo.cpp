#include "Structure.h"

using namespace std;
using namespace Structure;

ClassInfo::ClassInfo()
{
	BaseUri = ".\\";
	StudentList = make_shared<StudentInfo>();
	ofstream stuFile(BaseUri + StuUri, ios::trunc);
	StudentList->SaveStudentInfo(stuFile);
	stuFile.close();
}

ClassInfo::ClassInfo(string _uri)
{
	BaseUri = _uri;
	ifstream _file(BaseUri + "Class.dat", ios::in);
	// 第一行为基地址(不支持空格)
	std::string str;
	_file >> str;
	BaseUri = str;
	// 第二行为学生列表所在位置(相对于基地址)
	_file >> str;
	StuUri = str;
	ifstream stuFile(BaseUri + StuUri, ios::in);
	StudentList = make_shared<StudentInfo>(stuFile);
	stuFile.close();
	// 剩下各行为课程id+课程名称+课程学分
	int id, point;
	char* buffer = new char[sizeof(int) / sizeof(char)];
	while (!_file.eof() || !_file.fail())
	{
		_file >> id >> str >> point;
		auto classData = make_shared<ClassData>(id, str, point);
		ifstream classFile(BaseUri + Snippet.EncodeBase64(to_string(id)));
		classData->ReadFromStream(classFile);
		classFile.close();
		Data.emplace(id, classData);
	}
	StudentList->JoinClassInfo(Data);
}

void ClassInfo::JoinStudentInfo(StudentInfo* _studentInfo)
{
	StudentList = shared_ptr<StudentInfo>(_studentInfo);
	StudentList->JoinClassInfo(Data);
}

std::shared_ptr<ClassData> ClassInfo::GetClassData(int _id)
{
	return Data.find(_id) == Data.end() ? nullptr : Data[_id];
}

std::vector<ClassItem> ClassInfo::GetStudentData(int _id)
{
	auto l = StudentList->GetClasses(_id);
	vector<ClassItem> result = {};
	for (auto i = l.begin(); i != l.end(); i++)
	{
		result.push_back(ClassItem(i->first, i->second->Name, i->second->Point, i->second->GetScore(_id)));
	}
	return result;
}

void ClassInfo::UpdateClassData(ClassData& _data)
{
	auto d = Data.find(_data.ID);
	if (d == Data.end())
	{
		_data.InitialUpdate();
		auto ptr = make_shared<ClassData>(_data);
		Data.emplace(_data.ID, ptr);
		StudentList->UpdateClassData(ptr);
	}
	else
	{
		d->second->ScanUpdate(_data);
		StudentList->UpdateClassData(d->second);
	}
	_data.ClearModifiedList();
}

void ClassInfo::SaveClassInfo(bool _textMode)
{
	ofstream _file(BaseUri + "Class.dat", ios::trunc);
	ofstream classFile(BaseUri + StuUri, ios::trunc);
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
			ofstream classFile(BaseUri + Snippet.EncodeBase64(to_string(i->second->ID)), ios::trunc);
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
			ofstream classFile(BaseUri + Snippet.EncodeBase64(to_string(i->second->ID)), ios::trunc);
			i->second->SaveClassData(classFile, _textMode);
			classFile.close();
		}
	}
	_file.close();
}

void ClassInfo::RefreshStatistics()
{
	StudentList->RefreshAverageScore();
}
