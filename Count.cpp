#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Count(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl
            << "           统计系统           " << endl << endl
            << string(32, '#') << endl << endl
            << "       1.平均学分绩统计        " << endl
            << "       2.单项学分绩统计        " << endl
            << "         3. 停止查询          " << endl
            << string(32, '#') << endl << endl;
        cout << "请输入指令前的数字选项：";
        int i;
        cin >> i;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        switch (i)
        {
        case 1:
        {
            cout << "已进入平均学分绩统计模式" << endl;
            float max, min;
            cout << "请输入平均学分绩上限(负数为无限)：" << endl;
            cin >> max;
            if (cin.fail())
                throw "不合法的输入数据，请重新输入";
            cout << "请输入平均学分绩下限(负数为无限)：" << endl;
            cin >> min;
            if (cin.fail())
                throw "不合法的输入数据，请重新输入";
            auto StuData = info.CountAverageBetween(min, max);
            sort(StuData.begin(), StuData.end());
            cout << "ID          成绩           " << endl;
            for (auto j = StuData.begin(); j != StuData.end(); j++)
            {
                cout << setiosflags(ios::left)
                    << setw(12) << j->first
                    << setw(12) << j->second << endl;
            }
            cout << endl << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 4;
            break;
        }
        case 2:
        {
            cout << "已进入单项学分绩统计模式" << endl;
            int id;
            cout << "请输入课程ID(输入负数以退出)：" << endl;
            cin >> id;
            if (cin.fail())
                throw "不合法的输入数据，请重新输入";
            float max, min;
            cout << "请输入平均学分绩上限(负数为无限)：" << endl;
            cin >> max;
            if (cin.fail())
                throw "不合法的输入数据，请重新输入";
            cout << "请输入平均学分绩下限(负数为无限)：" << endl;
            cin >> min;
            if (cin.fail())
                throw "不合法的输入数据，请重新输入";
            auto StuData = info.GetClassData(id)->CountAverageBetween(min, max);
            sort(StuData.begin(), StuData.end());
            cout << "ID          成绩           " << endl;
            for (auto j = StuData.begin(); j != StuData.end(); j++)
            {
                cout << setiosflags(ios::left)
                    << setw(12) << j->first
                    << setw(12) << j->second << endl;
            }
            cout << endl << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 4;
            break;
            break;
        }
        case 3:
            return 0;
            break;
        default:
            throw "无法识别的序列号，请重新输入。";
            break;
        }

        return 0;
    }
}