#include "..\Include\Register.h"

using namespace std;

namespace Register
{
	void CreateKey(const std::wstring& dir, const std::wstring& key, const std::string& value)
	{
        std::wstring_convert<codecvt_utf8<wchar_t>> converter = {};
        wstring wstr = converter.from_bytes(value);
        HKEY hKey;
        if (ERROR_SUCCESS == ::RegCreateKey(HKEY_CURRENT_USER, dir.c_str(), &hKey))
        {
            if (ERROR_SUCCESS == ::RegSetValueEx(hKey, key.c_str(), 0, REG_SZ, (BYTE*)wstr.c_str(), sizeof(wstr)))
                cout << "ע�����ӳɹ���" << endl;
            else
                cout << "ע������������쳣����" << endl;
        }
        else
            cout << "ע������������쳣����" << endl;
	}
}