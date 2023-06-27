#pragma once

#include <iostream>
#include <fstream>
#include "Stucture.h"

namespace Processor
{
	// �½��༶��Ϣ
	void AddClassInfo(const int ID, const char* Name, const int Point = 1);
	// ��ȡ�༶��Ϣ
	void ReadClassInfo(const int ID, char** pName, int* pPoint);
	// ��ȡָ���ļ���¼��γ������ļ�
	void InputClassData(const char* Path);
	// ��ȡ�û���������¼��γ������ļ�
	void InputClassData(std::istream& IStream = std::cin, std::ostream& OStream = std::cout);
	// 

}