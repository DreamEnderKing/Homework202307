#include "Stucture.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Stucture;

ClassData::ClassData(int _id, std::string _name, int _point, ifstream& _file)
	: ID(_id), Name(_name), Point(_point)
{
	// 默认应当为升序排列
	Arranged = true;
	int lastID = -1;
	while (!_file.eof() || _file.fail())
	{
		int id, score;
		_file >> id >> score;
		Arranged = (!Arranged) ? false : (id >= lastID);
		lastID = Arranged ? id : lastID;
		StudentList.emplace(id, score);
	}
	if (_file.fail())
		cout << "课程成绩数据库异常！";
}

int ClassData::GetScore(int _id)
{
	auto i = StudentList.find(_id);
	return (i == StudentList.end()) ? -1 : i->second;
}

void ClassData::UpdateStudentData(int _id, int _score)
{
	std::map<int, int>::iterator i;
	bool found = false;
	if (Arranged)
	{
		i = lower_bound(StudentList.begin(), StudentList.end(), make_pair(_id, -1));
		found = (i != StudentList.end()) || (i->first == _id);
	}
	else
	{
		i = StudentList.find(_id);
		found = (i != StudentList.end());
	}
	if (!found)
	{
		if (Arranged)
			StudentList.insert(i, make_pair(_id, _score));
		else
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
	// 拷贝一份学生数据
	auto _new = _newData.StudentList;
	for (auto i = StudentList.begin(); i != StudentList.end(); i++)
	{
		// 查找新数据里对应键值对
		auto j = _newData.Arranged ?
			lower_bound(_new.begin(), _new.end(), make_pair(i->first, -1)) :
			_new.find(i->first);
		auto found = _newData.Arranged ?
			(j != _new.end() || i->first == j->first) :
			(j != _new.end());
		// 如果没有找到，说明该数据已删除
		if (!found)
		{
			auto _id = i->first, _score = i->second;
			StudentList.erase(i->first);
			ModifiedList.emplace(Deleted, make_pair(_id, _score));
		}
		else
		{
			// 如果数据不一致，说明该数据已改动
			if (i->second != j->second)
			{
				i->second = j->second;
				ModifiedList.emplace(Modified, make_pair(i->first, j->second));
			}
			// 删除已经搜索完成的数据
			_new.erase(j->first);
		}
		// 如果还存在数据，这部分数据一定是原来没有的
		for (auto j = _new.begin(); j != _new.end(); j++)
		{
			auto _id = j->first, _score = j->second;
			if (Arranged)
			{
				auto l = lower_bound(StudentList.begin(), StudentList.end(), make_pair(_id, -1));
				StudentList.insert(l, make_pair(_id, _score));
			}
			else
				StudentList.emplace(_id, _score);
			ModifiedList.emplace(Added, make_pair(_id, _score));
		}
	}
}

void ClassData::ArrangeData()
{
	sort(StudentList.begin(), StudentList.end());
	Arranged = true;
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