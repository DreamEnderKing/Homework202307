#include <iostream>
#include <iomanip>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Search(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       ѧ���ɼ�����ϵͳ        " << endl
            << "           ��ѯϵͳ           " << endl << endl
            << string(32, '#') << endl << endl
            << "         1.����ɼ���         " << endl
            << "         2.������ݱ�          " << endl
            << "         3. ֹͣ��ѯ          " << endl
            << string(32, '#') << endl << endl;
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        switch (i) {
        case 1:
        {
            int id;
            cout << "������ѧ��ID��" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            cout << endl << string(32, '-') << endl << endl;
            cout << "ID: " << id << "ѧ���ĳɼ�����" << endl;
            float t = 0, p = 0;
            cout << "--------------------------------" << endl
                <<  "�γ�����        ID     ����  �ɼ�" << endl;
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
            cout << "��ѧ��:     " << p << endl;
            cout << "ƽ��ѧ�ּ�:  " << setiosflags(ios::fixed) << setprecision(2) << t / p << endl;
            cout << string(32, '-') << endl << endl;
            cout << "����������˳�......" << endl;
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
            throw "�޷�ʶ������кţ����������롣";
            break;
        }
    }
}