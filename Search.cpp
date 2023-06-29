#include <iostream>
#include <iomanip>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Search(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl
            << "           查询系统           " << endl << endl
            << string(32, '#') << endl << endl
            << "         1.输出成绩单         " << endl
            << "         2.输出数据表          " << endl
            << "         3. 停止查询          " << endl
            << string(32, '#') << endl << endl;
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        switch (i) {
        case 1:
        {
            int id;
            cout << "请输入学生ID：" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            cout << endl << string(32, '-') << endl << endl;
            cout << "ID: " << id << "学生的成绩单：" << endl;
            float t = 0, p = 0;
            cout << "--------------------------------" << endl
                <<  "课程名称        ID     绩点  成绩" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                t += j->Point * j->ClassPoint, p += j->ClassPoint;
                cout << setiosflags(ios::left)
                    << setw(15) << j->Name << ' '
                    << setw(8) << j->ID << ' '
                    << setw(3) << j->ClassPoint << ' '
                    << setw(3) << j->Point << endl;
            }
            cout << string(32, '-') << endl;
            cout << "总学分:     " << p << endl;
            cout << "平均学分绩:  " << setiosflags(ios::fixed) << setprecision(2) << t / p << endl;
            cout << string(32, '-') << endl << endl;
            cout << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
            return 0;
            break;
        default:
            throw "无法识别的序列号，请重新输入。";
            break;
        }
    }
}