#include <iostream>
#include <strstream>
#include "..\Include\Displayer.h"

using namespace Structure;
using namespace std;

namespace Displayer
{
    int Cover(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl << endl
            << string(32, '#') << endl << endl
            << "           主菜单             " << endl << endl
            << "         1. 录入系统          " << endl
            << "         2. 修改系统          " << endl
            << "         3. 查询系统          " << endl
            << "         4. 统计系统          " << endl
            << "         5. 退出系统          " << endl << endl
            << string(32, '#') << endl << endl;
        cout << "请输入指令前的数字选项：";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        switch (i) {
        case 1:
            cout << "即将进入录入系统......" << endl;
            return 1;
        case 2:
            cout << "即将进入修改系统......" << endl;
            return 2;
        case 3:
            cout << "即将进入查询系统......" << endl;
            return 3;
        case 4:
            cout << "即将进入统计系统......" << endl;
            return 4;
        case 5:
            cout << "是否确认退出(y/n)？" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
                return -1;
            else
                return 0;
            break;
        default:
            throw "无法识别的序列号，请重新输入。";
            break;
        }



        
        ClassInfo cInfo("E:\\bin\\");
        auto c = cInfo.GetClassData(1001);
        c->UpdateStudentData(3, 80);
        cInfo.UpdateClassData(*c);
        auto ss = cInfo.GetStudentData(1);
        cInfo.SaveClassInfo();

        return 0;
    }
}