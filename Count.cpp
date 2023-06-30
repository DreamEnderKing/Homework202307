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
            << "       ѧ���ɼ�����ϵͳ        " << endl
            << "           ͳ��ϵͳ           " << endl << endl
            << string(32, '#') << endl << endl
            << "       1.ƽ��ѧ�ּ�ͳ��        " << endl
            << "       2.����ѧ�ּ�ͳ��        " << endl
            << "         3. ֹͣ��ѯ          " << endl
            << string(32, '#') << endl << endl;
        cout << "������ָ��ǰ������ѡ�";
        int i;
        cin >> i;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        switch (i)
        {
        case 1:
        {
            cout << "�ѽ���ƽ��ѧ�ּ�ͳ��ģʽ" << endl;
            float max, min;
            cout << "������ƽ��ѧ�ּ�����(����Ϊ����)��" << endl;
            cin >> max;
            if (cin.fail())
                throw "���Ϸ����������ݣ�����������";
            cout << "������ƽ��ѧ�ּ�����(����Ϊ����)��" << endl;
            cin >> min;
            if (cin.fail())
                throw "���Ϸ����������ݣ�����������";
            auto StuData = info.CountAverageBetween(min, max);
            sort(StuData.begin(), StuData.end());
            cout << "ID          �ɼ�           " << endl;
            for (auto j = StuData.begin(); j != StuData.end(); j++)
            {
                cout << setiosflags(ios::left)
                    << setw(12) << j->first
                    << setw(12) << j->second << endl;
            }
            cout << endl << "����������˳�......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 4;
            break;
        }
        case 2:
        {
            cout << "�ѽ��뵥��ѧ�ּ�ͳ��ģʽ" << endl;
            int id;
            cout << "������γ�ID(���븺�����˳�)��" << endl;
            cin >> id;
            if (cin.fail())
                throw "���Ϸ����������ݣ�����������";
            float max, min;
            cout << "������ƽ��ѧ�ּ�����(����Ϊ����)��" << endl;
            cin >> max;
            if (cin.fail())
                throw "���Ϸ����������ݣ�����������";
            cout << "������ƽ��ѧ�ּ�����(����Ϊ����)��" << endl;
            cin >> min;
            if (cin.fail())
                throw "���Ϸ����������ݣ�����������";
            auto StuData = info.GetClassData(id)->CountAverageBetween(min, max);
            sort(StuData.begin(), StuData.end());
            cout << "ID          �ɼ�           " << endl;
            for (auto j = StuData.begin(); j != StuData.end(); j++)
            {
                cout << setiosflags(ios::left)
                    << setw(12) << j->first
                    << setw(12) << j->second << endl;
            }
            cout << endl << "����������˳�......" << endl;
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
            throw "�޷�ʶ������кţ����������롣";
            break;
        }

        return 0;
    }
}