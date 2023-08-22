#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <locale>

#include ".\Include\Displayer.h"
#include ".\Include\Register.h"

#pragma warning(disable:4996)

using namespace std;
using namespace Displayer;

int main()
{
    bool success = false;
    Structure::ClassInfo *pinfo = nullptr;
    while (!success)
    {
        const wstring data_set = L"Software\\DreamEnderKing\\Project2023Summer";
        const wstring key = L"path";
        const string key_files[] = { "class.dat", "student.dat"};
        string path = "";
        try
        {
            if (!Register::FindKey(data_set, key, path))
                throw "注册表项未找到！";
            auto result = Register::FileExists(path, vector<string>(key_files, key_files + 2));
            if (result->size() > 1 && (*result)[0] && (*result)[1])
            {
                pinfo = new Structure::ClassInfo(path);
                success = true;
            }
            else
            {
                cout << "数据库文件残缺，是否创建全新的数据库(y/n)？" << endl;
                cin.seekg(ios::end);
                char c;
                cin >> c;
                if (c == 'y' || c == 'Y')
                {
                    pinfo = new Structure::ClassInfo(path, true);
                    cout << "数据库初始化完毕。" << endl;
                    system("pause");
                    system("cls");
                    success = true;
                }
                else
                    throw "用户已取消数据库初始化操作";
            }
            delete result;
        }
        catch(const char* Exception)
        {
            cout << "Fatal Error: " << Exception << endl;
            cout << "是否重新注册(y/n)？" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (!(c == 'y' || c == 'Y'))
            {
                cout << "用户已取消注册，程序异常终止。" << endl;
                system("pause");
                return -1;
            }
            // 重新注册
            cout << "请输入新的路径(已存在的文件夹)：" << endl;
            cin.seekg(ios::end);
            char str[256] = { '\0' };
            cin.getline(str, 256);
            // 如果路径以'\'结尾，删除之
            int len = strlen(str);
            if (str[len - 1] == '\\')
                str[len - 1] = '\0', len--;
            string val = str;
            Register::CreateKey(data_set, key, val);
            system("pause");
            system("cls");
        }
    }            
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