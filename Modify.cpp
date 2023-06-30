#include <iostream>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Modify(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl
            << "           修改系统           " << endl << endl
            << string(32, '#') << endl << endl;
        int id, stuId;
        cout << "请输入课程ID(输入负数以退出)：" << endl;
        cin >> id;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        if (id < 0)
            return 0;
        auto cl = info.GetClassData(id);
        if (cl == nullptr)
        {
            cout << "课程ID不存在，如要添加，请前往录入界面。" << endl;
            sleep(2000);
            return 1;
        }
        cout << "请输入学生ID：" << endl;
        cin >> stuId;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        int i = cl->GetScore(stuId);
        if (i < 0)
        {
            cout << "检测到学生数据不存在，是否添加(y/n)？" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                cout << "请输入学生成绩：" << endl;
                cin >> i;
                cl->UpdateStudentData(stuId, i);
                info.UpdateClassData(*cl);
                cout << "数据新增完毕。" << endl;
                sleep(2000);
            }
            return 2;
        }
        else
        {
            cout << "原成绩为：" << i << "，是否确认修改(y/n)？" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                cout << "请输入学生成绩：" << endl;
                cin >> i;
                cl->UpdateStudentData(stuId, i);
                info.UpdateClassData(*cl);
                cout << "数据修改完毕。" << endl;
                sleep(2000);
            }
            return 2;
        }
    }
}