#include "Structure.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Structure;

ClassData::ClassData(const int _id, const std::string _name, const int _point, ifstream& _file)
	: ID(_id), Name(_name), Point(_point)
{
	while (!_file.eof() && !_file.fail())
	{
		int id, score;
		_file >> id >> score;
		StudentList.emplace(id, score);
	}
	if (_file.fail())
		MyDebugError("�γ̳ɼ����ݿ��쳣��");
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
		ModifiedList.push_back(ModifyLog(Added, _id, _score));
	}
	else
	{
		ModifiedList.push_back(ModifyLog(Modified, _id, _score, i->second));
		i->second = _score;
	}
}

void ClassData::DeleteStudentData(int _id)
{
	auto i = StudentList.find(_id);
	if (i != StudentList.end())
	{
		auto _score = i->second;
		StudentList.erase(_id);
		ModifiedList.push_back(ModifyLog(Deleted, _id, _score));
	}
}

void ClassData::ScanUpdate(const ClassData& _newData)
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
			ModifiedList.push_back(ModifyLog(Deleted, _id, _score));
		}
		else
		{
			// ������ݲ�һ�£�˵���������ѸĶ�
			if (i->second != j->second)
			{
				ModifiedList.push_back(ModifyLog(Modified, i->first, j->second, i->second));
				i->second = j->second;
			}
			// ɾ���Ѿ�������ɵ�����
			_new.erase(j->first);
		}
		// ������������ݣ��ⲿ������һ����ԭ��û�е�
		for (auto j = _new.begin(); j != _new.end(); j++)
		{
			auto _id = j->first, _score = j->second;
			StudentList.emplace(_id, _score);
			ModifiedList.push_back(ModifyLog(Added, _id, _score));
		}
	}
}

void ClassData::SaveClassData(std::ofstream& _file, bool _textMode) const
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

std::vector<ModifyLog> ClassData::GetModifiedList() const
{
	return ModifiedList;
}
