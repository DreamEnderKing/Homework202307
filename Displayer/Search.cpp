#include <iostream>
#include <iomanip>
#include "..\Include\Displayer.h"

using namespace std;

namespace Displayer
{
    int Search(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl
            << "           查询系统           " << endl << endl
            << string(32, '#') << endl << endl
            << "       1.输出个人成绩单        " << endl
            << "       2.输出课程成绩单        " << endl
            << "       3.输出个人数据表        " << endl
            << "       4.输出课程数据表        " << endl
            << "         5. 停止查询          " << endl
            << string(32, '#') << endl << endl;
        cout << "请输入指令前的数字选项：";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        switch (i) {
        case 1:
        {
            cout << "已进入个人成绩单输出模式" << endl;
            int id;
            cout << "请输入学生ID：" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            if (list.size() == 0)
            {
                cout << "学生暂无成绩记录或ID错误，请检查输入。" << endl;
                system("pause");
                return 3;
            }
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
            cout << "已进入课程成绩单输出模式" << endl;
            int id;
            cout << "请输入课程ID：" << endl;
            cin >> id;
            auto _list = info.GetClassData(id);
            if (_list == nullptr)
            {
                cout << "课程暂无成绩记录或ID错误，请检查输入。" << endl;
                system("pause");
                return 3;
            }
            auto list = _list->CountAverageBetween(-1, -1);
            cout << endl << string(32, '-') << endl << endl;
            cout << "ID: " << id << "课程的成绩单：" << endl;
            float t = 0, max = -1, min = FLT_MAX;
            vector<int> max_id = {}, min_id = {};
            cout << "--------------------------------" << endl
                <<  "ID           成绩" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                t += j->second;
                if (j->second > max)
                    max = j->second, max_id.clear(), max_id.push_back(j->first);
                else if (j->second == max)
                    max_id.push_back(j->first);
                if (j->second < min)
                    min = j->second, min_id.clear(), min_id.push_back(j->first);
                else if (j->second == min)
                    min_id.push_back(j->first);
                cout << setiosflags(ios::left)
                    << setw(12) << j->first << ' '
                    << setw(12) << j->second << endl;
            }
            cout << string(32, '-') << endl;
            cout << "总学分:     " << _list->Point << endl;
            cout << "平均学分绩:  " << setiosflags(ios::fixed) << setprecision(2) << t / list.size() << endl;
            cout << "最高分：" << max << "，最低分：" << min << endl;
            cout << "最高分ID：" << endl;
            for (auto j = max_id.begin(); j != max_id.end(); j++)
                cout << *j << ' ';
            cout << endl << "最低分ID：" << endl;
            for (auto j = min_id.begin(); j != min_id.end(); j++)
                cout << *j << ' ';
            cout << endl << string(32, '-') << endl << endl;
            cout << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 3:
        {
            cout << "已进入个人数据表输出模式" << endl;
            int id;
            cout << "请输入学生ID：" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            if (list.size() == 0)
            {
                cout << "学生暂无成绩记录或ID错误，请检查输入。" << endl;
                system("pause");
                return 3;
            }
            cout << "数据表格式：" << "课程ID 绩点 成绩" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                cout << j->ID << ' ' << j->ClassPoint << ' ' << j->Point << endl;
            }
            cout << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 4:
        {
            cout << "已进入课程数据表输出模式" << endl;
            int id;
            cout << "请输入课程ID：" << endl;
            cin >> id;
            auto _list = info.GetClassData(id);
            if (_list == nullptr)
            {
                cout << "课程暂无成绩记录或ID错误，请检查输入。" << endl;
                system("pause");
                return 3;
            }
            auto list = _list->CountAverageBetween(-1, -1);
            cout << "数据表格式：" << "学生ID 成绩" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                cout << j->first << ' ' << j->second << endl;
            }
            cout << "单击任意键退出......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 5:
            return 0;
            break;
        default:
            throw "无法识别的序列号，请重新输入。";
            break;
        }
    }
}