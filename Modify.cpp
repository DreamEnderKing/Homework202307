#include <iostream>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Modify(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       ѧ���ɼ�����ϵͳ        " << endl
            << "           �޸�ϵͳ           " << endl << endl
            << string(32, '#') << endl << endl;
        int id, stuId;
        cout << "������γ�ID(���븺�����˳�)��" << endl;
        cin >> id;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        if (id < 0)
            return 0;
        auto cl = info.GetClassData(id);
        if (cl == nullptr)
        {
            cout << "�γ�ID�����ڣ���Ҫ��ӣ���ǰ��¼����档" << endl;
            sleep(2000);
            return 1;
        }
        cout << "������ѧ��ID��" << endl;
        cin >> stuId;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        int i = cl->GetScore(stuId);
        if (i < 0)
        {
            cout << "��⵽ѧ�����ݲ����ڣ��Ƿ����(y/n)��" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                cout << "������ѧ���ɼ���" << endl;
                cin >> i;
                cl->UpdateStudentData(stuId, i);
                info.UpdateClassData(*cl);
                cout << "����������ϡ�" << endl;
                sleep(2000);
            }
            return 2;
        }
        else
        {
            cout << "ԭ�ɼ�Ϊ��" << i << "���Ƿ�ȷ���޸�(y/n)��" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                cout << "������ѧ���ɼ���" << endl;
                cin >> i;
                cl->UpdateStudentData(stuId, i);
                info.UpdateClassData(*cl);
                cout << "�����޸���ϡ�" << endl;
                sleep(2000);
            }
            return 2;
        }
    }
}