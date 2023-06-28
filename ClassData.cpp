#include "Stucture.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Stucture;

ClassData::ClassData(int _id, std::string _name, int _point, ifstream& _file)
	: ID(_id), Name(_name), Point(_point)
{
	int lastID = -1;
	while (!_file.eof() || _file.fail())
	{
		int id, score;
		_file >> id >> score;
		StudentList.emplace(id, score);
	}
	if (_file.fail())
		cout << "�γ̳ɼ����ݿ��쳣��";
}

int ClassData::GetScore(int _id)
{
	auto i = StudentList.find(_id);
	return (i == StudentList.end()) ? -1 : i->second;
}

void ClassData::UpdateStudentData(int _id, int _score)
{
	auto i = StudentList.find(_id);
	if (i == StudentList.end())
	{
		StudentList.emplace(_id, _score);
		ModifiedList.emplace(Added, make_pair(_id, _score));
	}
	else
	{
		i->second = _score;
		ModifiedList.emplace(Modified, make_pair(_id, _score));
	}
}

void ClassData::DeleteStudentData(int _id)
{
	auto i = StudentList.find(_id);
	if (i != StudentList.end())
	{
		auto _score = i->second;
		StudentList.erase(_id);
		ModifiedList.emplace(Deleted, make_pair(_id, _score));
	}
}

void ClassData::ScanUpdate(ClassData& _newData)
{
	// ����һ��ѧ������
	map<int, int> _new = _newData.StudentList;
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
	{
		// �������������Ӧ��ֵ��
		auto j = _new.find(i->first);
		// ���û���ҵ���˵����������ɾ��
		if (j == _new.end())
		{
			auto _id = i->first, _score = i->second;
			StudentList.erase(i->first);
			ModifiedList.emplace(Deleted, make_pair(_id, _score));
		}
		else
		{
			// ������ݲ�һ�£�˵���������ѸĶ�
			if (i->second != j->second)
			{
				i->second = j->second;
				ModifiedList.emplace(Modified, make_pair(i->first, j->second));
			}
			// ɾ���Ѿ�������ɵ�����
			_new.erase(j->first);
		}
		// ������������ݣ��ⲿ������һ����ԭ��û�е�
		for (auto j = _new.begin(); j != _new.end(); j++)
		{
			auto _id = j->first, _score = j->second;
			StudentList.emplace(_id, _score);
			ModifiedList.emplace(Added, make_pair(_id, _score));
		}
	}
}

void ClassData::SaveClassData(std::ofstream& _file, bool _textMode)
{
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
	{
		if (_textMode)
		{
			_file << i->first << ' ' << i->second << endl;
		}
		else
			_file << i->first << i->second;
	}
}