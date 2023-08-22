#pragma once

#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <io.h>
#include <codecvt>

namespace Register
{
	// ��ע����в�ѯָ���ļ����µļ�ֵ��
	bool FindKey(const std::wstring& dir, const std::wstring& key, std::string& result);
	// ��ע����д���ָ���ļ����µļ�ֵ��
	void CreateKey(const std::wstring& dir, const std::wstring& key, const std::string& value);
	// ���ļ�����Ѱ��ָ���ļ��б�
	std::vector<bool>* FileExists(const std::string& dir, const std::vector<std::string>& files);
}