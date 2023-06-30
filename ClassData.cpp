#include "Structure.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Structure;

ClassData::ClassData(const int _id, const std::string _name, const int _point)
	: ID(_id), Name(_name), Point(_point)
{
}

void ClassData::ReadFromStream(istream& _file)
{
	while (!_file.eof())
	{
		int id, score;
		_file >> id >> score;
		StudentList.emplace(id, score);
	}
}

ClassData::~ClassData()
{

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

void ClassData::InitialUpdate()
{
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
		ModifiedList.push_back(ModifyLog(Added, i->first, i->second));
}

void ClassData::ScanUpdate(const ClassData& _newData)
{
	// 拷贝一份学生数据
	map<int, int> _new = _newData.StudentList;
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
	{
		// 查找新数据里对应键值对
		auto j = _new.find(i->first);
		// 如果没有找到，说明该数据已删除
		if (j == _new.end())
		{
			auto _id = i->first, _score = i->second;
			StudentList.erase(i->first);
			ModifiedList.push_back(ModifyLog(Deleted, _id, _score));
		}
		else
		{
			// 如果数据不一致，说明该数据已改动
			if (i->second != j->second)
			{
				ModifiedList.push_back(ModifyLog(Modified, i->first, j->second, i->second));
				i->second = j->second;
			}
			// 删除已经搜索完成的数据
			_new.erase(j->first);
		}
	}
	// 如果还存在数据，这部分数据一定是原来没有的
	for (auto j = _new.begin(); j != _new.end(); j++)
	{
		auto _id = j->first, _score = j->second;
		StudentList.emplace(_id, _score);
		ModifiedList.push_back(ModifyLog(Added, _id, _score));
	}
}

void ClassData::ClearModifiedList()
{
	ModifiedList.clear();
}

void ClassData::SaveClassData(std::ostream& _file, bool _textMode) const
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

std::vector<std::pair<int, float>> ClassData::CountAverageBetween(float min, float max)
{
	vector<pair<int, float>> result = {};
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
	{
		if (((i->second >= min) || min < 0)
			&& ((i->second <= max) || max < 0))
			result.push_back(make_pair(i->first, i->second));
	}
	return result;
}

float Structure::ClassData::GetAverageScore()
{
	float t = 0;
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
		t += i->second;
	return t / StudentList.size();
}
