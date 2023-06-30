#include "Structure.h"

using namespace std;
using namespace Structure;

StudentInfo::StudentInfo()
{

}

StudentInfo::StudentInfo(istream& _file)
{
	while (!_file.eof() && !_file.fail())
	{
		int id, total, classId;
		float avg;
		_file >> id >> avg >> total;
		vector<pair<int, shared_ptr<ClassData>>> c = {};
		while(true)
		{
			_file >> classId;
			if (classId == -1)
				break;
			c.push_back(make_pair(classId, nullptr));
		}
		Data.emplace(id, make_pair(StudentBriefData(avg, total), c));
	}
}

vector<pair<int, std::shared_ptr<ClassData>>> StudentInfo::GetClasses(int _id)
{
	return (Data.find(_id) == Data.end()) ? vector<pair<int, shared_ptr<ClassData>>>() : Data[_id].second;
}

void StudentInfo::UpdateClassData(const shared_ptr<ClassData>& _class)
{
	auto modified = _class->GetModifiedList();
	for (auto i = modified.begin(); i != modified.end(); i++)
	{
		switch (i->status)
		{
		case Added:
		{
			// 查询学生是否存在
			auto j = Data.find(i->stuId);
			// 如果不存在，创建新的学生条目；否则修改已有的学生条目
			if (j == Data.end())
			{
				auto c = vector<pair<int, shared_ptr<ClassData>>>();
				c.push_back(make_pair(_class->ID, _class));
				Data.emplace(i->stuId, make_pair(StudentBriefData(i->score, _class->Point), c));
			}
			else
			{
				auto oldAvg = j->second.first.averageScore;
				auto oldPoint = j->second.first.totalPoint;
				j->second.first.totalPoint = oldPoint + _class->Point;
				j->second.first.averageScore = (oldAvg * oldPoint + i->score) / j->second.first.totalPoint;
				j->second.second.push_back(make_pair(_class->ID, _class));
			}
			break;
		}
		case Modified:
		{
			auto j = Data.find(i->stuId);
			if (j == Data.end())
			{
				Snippet.MyDebugError("学生数据库异常！");
				break;
			}
			auto oldAvg = j->second.first.averageScore;
			auto oldPoint = j->second.first.totalPoint;
			j->second.first.averageScore = (oldAvg * oldPoint - i->oldScore * _class->Point + i->score * _class->Point) / oldPoint;
			break;
		}
		case Deleted:
		{
			auto j = Data.find(i->stuId);
			if (j == Data.end())
			{
				Snippet.MyDebugError("学生数据库异常！");
				break;
			}
			auto oldAvg = j->second.first.averageScore;
			auto oldPoint = j->second.first.totalPoint;
			j->second.first.totalPoint = oldPoint - _class->Point;
			j->second.first.averageScore = (oldAvg * oldPoint - i->score * _class->Point) / j->second.first.totalPoint;
			for (int k = 0; k < j->second.second.size(); k++)
			{
				auto l = &(j->second.second[k]);
				auto endElement = j->second.second.end() - 1;
				if (l->first == _class->ID)
				{
					l->first = endElement->first;
					l->second = endElement->second;
					j->second.second.pop_back();
				}
			}
			break;
		}
		}
	}
}

StudentInfo::~StudentInfo()
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		for (auto j = i->second.second.begin(); j != i->second.second.end(); j++)
		{
			j->second.reset();
		}
	}

}

void StudentInfo::JoinClassInfo(const map<int, shared_ptr<ClassData>>& _classInfo)
{
	for (auto stu = Data.begin(); stu != Data.end(); stu++)
	{
		for (auto list = stu->second.second.begin(); list != stu->second.second.end(); list++)
		{
			auto r = _classInfo.find(list->first);
			if (r != _classInfo.end())
			{
				list->second = r->second;
			}
		}
	}
}

void StudentInfo::SaveStudentInfo(ostream& _file, bool _textMode)
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		if (_textMode)
		{
			_file << i->first << ' '
				<< i->second.first.averageScore << ' '
				<< i->second.first.totalPoint << endl;
			for (auto j = i->second.second.begin(); j != i->second.second.end(); j++)
			{
				_file << j->first << ' ';
			}
			_file << -1 << endl;
		}
		else
		{
			_file << i->first
				<< i->second.first.averageScore
				<< i->second.first.totalPoint;
			for (auto j = i->second.second.begin(); j != i->second.second.end(); j++)
			{
				_file << j->first;
			}
			_file << -1;
		}
	}
}

void StudentInfo::RefreshAverageScore()
{
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		int t = 0, p = 0;
		for (auto j = i->second.second.begin(); j != i->second.second.end(); j++)
		{
			p += j->second->Point;
			t += j->second->GetScore(i->first) * j->second->Point;
		}
		i->second.first.averageScore = ((float)t) / p;
		i->second.first.totalPoint = p;
	}
}

vector<pair<int, float>> StudentInfo::CountAverageBetween(float min, float max)
{
	vector<pair<int, float>> result = {};
	for (auto i = Data.begin(); i != Data.end(); i++)
	{
		if (((i->second.first.averageScore >= min) || min < 0)
			&& ((i->second.first.averageScore <= max) || max < 0))
			result.push_back(make_pair(i->first, i->second.first.averageScore));
	}
	return result;
}
