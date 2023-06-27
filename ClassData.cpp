#include "Stucture.h"
#include <iostream>

using namespace std;
using namespace Stucture;

ClassData::ClassData(int _id, std::string _name, int _point, ifstream& _file)
	: ID(_id), Name(_name), Point(_point)
{
	while (!_file.eof() || _file.fail())
	{
		int id, score;
		_file >> id >> score;
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

