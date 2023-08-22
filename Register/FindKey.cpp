#include "..\Include\Register.h"

using namespace std;

namespace Register
{
	bool FindKey(const std::wstring& dir, const std::wstring& key, std::string& result)
	{
        result = "";
		HKEY hKey;
        auto r = false;
        if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, dir.c_str(), 0, KEY_READ, &hKey))
        {
            WCHAR pathVal[256] = { 0 };
            DWORD dwSize = sizeof(pathVal);
            DWORD dwType = REG_SZ;
            if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, key.c_str(), NULL, &dwType, (LPBYTE)pathVal, &dwSize))
            {
                wstring wpath(pathVal);
                int len = WideCharToMultiByte(CP_ACP, 0, wpath.c_str(), wpath.size(), NULL, 0, NULL, NULL);
                char* buffer = new char[len + 1] { '\0' };
                WideCharToMultiByte(CP_ACP, 0, wpath.c_str(), wpath.size(), buffer, len, NULL, NULL);
                result.append(buffer);
                delete[] buffer;
                r = true;
            }
        }
        return r;
	}
}