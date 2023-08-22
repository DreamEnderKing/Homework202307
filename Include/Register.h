#pragma once

#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <io.h>
#include <codecvt>

namespace Register
{
	// 在注册表中查询指定文件夹下的键值对
	bool FindKey(const std::wstring& dir, const std::wstring& key, std::string& result);
	// 在注册表中创建指定文件夹下的键值对
	void CreateKey(const std::wstring& dir, const std::wstring& key, const std::string& value);
	// 在文件夹下寻找指定文件列表
	std::vector<bool>* FileExists(const std::string& dir, const std::vector<std::string>& files);
}