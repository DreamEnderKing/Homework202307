#pragma once

#include <iostream>
#include <fstream>
#include "Stucture.h"

namespace Processor
{
	// 新建班级信息
	void AddClassInfo(const int ID, const char* Name, const int Point = 1);
	// 读取班级信息
	void ReadClassInfo(const int ID, char** pName, int* pPoint);
	// 读取指定文件并录入课程数据文件
	void InputClassData(const char* Path);
	// 读取用户输入流并录入课程数据文件
	void InputClassData(std::istream& IStream = std::cin, std::ostream& OStream = std::cout);
	// 

}