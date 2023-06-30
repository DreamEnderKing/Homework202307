#include <iostream>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Input(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       学生成绩管理系统        " << endl
            << "           录入系统           " << endl << endl
            << string(32, '#') << endl << endl
            << "      1.通过文件路径录入       " << endl
            << "         2. 手动录入          " << endl
            << "         3. 停止录入          " << endl
            << string(32, '#') << endl << endl;
        cout << "请输入指令前的数字选项：";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "不合法的输入数据，请重新输入";
        switch (i)
        {
        case 1:
        {
            cout << "已进入文件路径输入模式。" << endl;
            cout << "请输入文件路径：" << endl;
            char path[256];
            cin.seekg(ios::end);
            cin.getline(path, 256);
            ifstream file(path);
            if (!file.is_open())
                throw "不合法的文件路径！";
            int id, point;
            string name;
            file >> id >> name >> point;
            Structure::ClassData data(id, name, point);
            data.ReadFromStream(file);
            info.UpdateClassData(data);
            cout << "数据录入完毕。";
            sleep(2000);
            return 1;
            break;
        }
        case 2:
        {
            cout << "已进入手动录入模式。" << endl;
            cout << "请输入课程序号：" << endl;
            int id, point;
            cin >> id;
            cout << "请输入课程名称(无空格)：" << endl;
            string name;
            cin >> name;
            cout << "请输入课程绩点：" << endl;
            cin >> point;
            Structure::ClassData data(id, name, point);
            int stuId = 0, score = 0;
            cout << "请循环输入学生学号+学生成绩，输入负数退出：" << endl;
            while (true)
            {
                cin >> stuId;
                if (stuId < 0) break;
                cin >> score;
                if (score < 0) break;
                if (cin.fail())
                {
                    cout << "错误的输入文本，请重新输入。" << endl;
                    cin.clear(), cin.seekg(ios::end);
                }
                data.UpdateStudentData(stuId, point);
            }
            info.UpdateClassData(data);
            cout << "数据录入完毕。";
            sleep(2000);
            return 1;
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