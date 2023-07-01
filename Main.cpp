#include <algorithm>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <locale>
#include <codecvt>

#include "Displayer.h"

#pragma warning(disable:4996)

using namespace std;
using namespace Displayer;

int main()
{
    bool success = false;
    Structure::ClassInfo *pinfo = nullptr;
    while (!success)
    {
        string path = "";
        // 查询注册表
        HKEY hKey;
        LPCTSTR data_set = L"Software\\DreamEnderKing\\Project2023Summer";
        try
        {
            if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, data_set, 0, KEY_READ, &hKey))
            {
                WCHAR pathVal[256] = { 0 };
                DWORD dwSize = sizeof(pathVal);
                DWORD dwType = REG_SZ;
                if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, L"path", NULL, &dwType, (LPBYTE)pathVal, &dwSize))
                {
                    wstring wpath(pathVal);
                    int len = WideCharToMultiByte(CP_ACP, 0, wpath.c_str(), wpath.size(), NULL, 0, NULL, NULL);
                    char* buffer = new char[len + 1] { '\0' };
                    WideCharToMultiByte(CP_ACP, 0, wpath.c_str(), wpath.size(), buffer, len, NULL, NULL);
                    path.append(buffer);
                    delete[] buffer;
                    // 获取文件夹下所有文件，确认全部可读可写
                    intptr_t hFile = 0;
                    struct _finddata_t _fileInfo;
                    bool has_Class = false, has_Stu = false;
                    if(_access(path.c_str(), 0) != 0)
                        throw "注册表文件夹打开失败！请重新注册！";
                    if ((hFile = _findfirst((path + "\\*").c_str(), &_fileInfo)) != -1)
                    {
                        do
                        {
                            if (!(_fileInfo.attrib & _A_SUBDIR))
                            {
                                string file(_fileInfo.name);
                                transform(file.begin(), file.end(), file.begin(), ::tolower);
                                has_Class = (file == "class.dat") ? true : has_Class;
                                has_Stu = (file == "student.dat") ? true : has_Stu;
                                if (_access((path + "\\" + file).c_str(), 6) != 0)
                                    throw path + "\\" + file + "没有读写权限！";
                            }
                        } while (_findnext(hFile, &_fileInfo) == 0);
                        if (has_Stu && has_Class)
                        {
                            cout << "数据库文件目录检查通过。" << endl;
                            pinfo = new Structure::ClassInfo(path);
                            system("pause");
                        }
                        else
                            throw "数据库关键文件残缺，请检查目录或全部删除后重新创建。";
                    }
                    else
                    {
                        cout << "该文件夹为空，是否创建全新的数据库(y/n)？" << endl;
                        cin.seekg(ios::end);
                        char c;
                        cin >> c;
                        if (c)
                        {
                            pinfo = new Structure::ClassInfo(path, true);
                            cout << "数据库初始化完毕。" << endl;
                            system("pause");
                            system("cls");
                        }
                        else
                            throw "用户已取消数据库初始化操作";
                    }
                    success = true;
                }
                else
                    throw "没有找到注册表项！";
            }
            else
                throw "没有找到注册表项！";
        }
        catch(const char* Exception)
        {
            cout << "Fatal Error: " << Exception << endl;
            // 重新注册
            cout << "请输入新的路径：" << endl;
            cin.seekg(ios::end);
            char str[256] = { '\0' };
            cin.getline(str, 256);
            // 如果路径以'\'结尾，删除之
            int len = strlen(str);
            if (str[len - 1] == '\\')
                str[len - 1] = '\0', len--;
            wstring_convert<codecvt_utf8<wchar_t>> converter = {};
            wstring wstr = converter.from_bytes(str);
            HKEY hTempKey;
            if (ERROR_SUCCESS == ::RegCreateKey(HKEY_CURRENT_USER, data_set, &hKey))
            {
                if (ERROR_SUCCESS == ::RegSetValueEx(hKey, L"path", 0, REG_SZ, (BYTE*)wstr.c_str(), sizeof(wstr)))
                    cout << "注册表添加成功！" << endl;
                else
                    cout << "注册过程中遇到异常错误。" << endl;
            }
            else
                cout << "注册过程中遇到异常错误。" << endl;
        }
    }
    system("cls");
    auto info = *pinfo;
    info.RefreshStatistics();
    // 操作的分支id
    // 0：封面打印；1：录入功能；2：修改功能；3：查询功能；4：统计功能
    int branch = 0;

    while (branch >= 0)
    {
        try
        {
            switch (branch)
            {
            case 0:
                branch = Cover(info);
                break;
            case 1:
                branch = Input(info);
                break;
            case 2:
                branch = Modify(info);
                break;
            case 3:
                branch = Search(info);
                break;
            case 4:
                branch = Count(info);
                break;
            }
        }
        catch (const char* Exception)
        {
            cout << "Fatal Error: " << endl << Exception << endl;
            cin.seekg(ios::end);
            while (!cin)
            {
                cin.clear();
                while (cin.get() != '\n')
                    continue;
            }
            system("pause");
        }
        std::system("cls");
    }
    info.SaveClassInfo();
    delete pinfo;
    return 0;
}