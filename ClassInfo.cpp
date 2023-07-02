#include "Structure.h"

using namespace std;
using namespace Structure;

ClassInfo::ClassInfo(string _uri, bool initial)
{
	BaseUri = _uri;
	if (initial)
	{
		StudentList = make_shared<StudentInfo>();
		SaveClassInfo();
		return;
	}
	ifstream _file(BaseUri + "\\Class.dat", ios::in);
	// ��һ��Ϊѧ���б�����λ��(����ڻ���ַ)
	std::string str;
	_file >> str;
	StuUri = str;
	ifstream stuFile(BaseUri + '\\' + StuUri, ios::in);
	StudentList = make_shared<StudentInfo>(stuFile);
	stuFile.close();
	// ʣ�¸���Ϊ�γ�id+�γ�����+�γ�ѧ��
	int id, point;
	char* buffer = new char[sizeof(int) / sizeof(char)];
	while (!_file.eof() || !_file.fail())
	{
		_file >> id >> str >> point;
		auto classData = make_shared<ClassData>(id, str, point);
		string p = BaseUri + '\\' + Snippet.EncodeBase64(to_string(id));
		ifstream classFile(p);
		if (!classFile.is_open())
		{
			cout << "�γ�ID��" << id << "�������ļ��޷��򿪣�" << endl
				<< "��Ӧ���ļ�Ϊ��" << p << endl
				<< "�Ƿ񽫸ÿγ̴ӿγ����ݿ���ɾ��(y/n)��" << endl;
			cin.seekg(ios::end);
			char c;
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				StudentList->DeleteClassData(id);
				break;
			}
			else
				throw "�γ����ݿ��ļ����ִ����û���ȡ���޸�������";
		}
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
	ofstream _file(BaseUri + "\\Class.dat", ios::trunc);
	ofstream classFile(BaseUri + '\\' + StuUri, ios::trunc);
	StudentList->SaveStudentInfo(classFile, _textMode);
	classFile.close();
	if (_textMode)
	{
		_file << StuUri << endl;
		for (auto i = Data.begin(); i != Data.end(); i++)
		{
			_file << i->first << ' '
				<< i->second->Name << ' '
				<< i->second->Point << endl;
			ofstream classFile(BaseUri + '\\' + Snippet.EncodeBase64(to_string(i->second->ID)), ios::trunc);
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
			ofstream classFile(BaseUri + '\\' + Snippet.EncodeBase64(to_string(i->second->ID)), ios::trunc);
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

vector<pair<int, float>> ClassInfo::CountAverageBetween(float min, float max)
{
	return StudentList->CountAverageBetween(min, max);
}
