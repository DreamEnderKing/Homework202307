#include <iostream>
#include <iomanip>
#include "..\Include\Displayer.h"

using namespace std;

namespace Displayer
{
    int Search(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       ѧ���ɼ�����ϵͳ        " << endl
            << "           ��ѯϵͳ           " << endl << endl
            << string(32, '#') << endl << endl
            << "       1.������˳ɼ���        " << endl
            << "       2.����γ̳ɼ���        " << endl
            << "       3.����������ݱ�        " << endl
            << "       4.����γ����ݱ�        " << endl
            << "         5. ֹͣ��ѯ          " << endl
            << string(32, '#') << endl << endl;
        cout << "������ָ��ǰ������ѡ�";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        switch (i) {
        case 1:
        {
            cout << "�ѽ�����˳ɼ������ģʽ" << endl;
            int id;
            cout << "������ѧ��ID��" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            if (list.size() == 0)
            {
                cout << "ѧ�����޳ɼ���¼��ID�����������롣" << endl;
                system("pause");
                return 3;
            }
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
            cout << "�ѽ���γ̳ɼ������ģʽ" << endl;
            int id;
            cout << "������γ�ID��" << endl;
            cin >> id;
            auto _list = info.GetClassData(id);
            if (_list == nullptr)
            {
                cout << "�γ����޳ɼ���¼��ID�����������롣" << endl;
                system("pause");
                return 3;
            }
            auto list = _list->CountAverageBetween(-1, -1);
            cout << endl << string(32, '-') << endl << endl;
            cout << "ID: " << id << "�γ̵ĳɼ�����" << endl;
            float t = 0, max = -1, min = FLT_MAX;
            vector<int> max_id = {}, min_id = {};
            cout << "--------------------------------" << endl
                <<  "ID           �ɼ�" << endl;
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
            cout << "��ѧ��:     " << _list->Point << endl;
            cout << "ƽ��ѧ�ּ�:  " << setiosflags(ios::fixed) << setprecision(2) << t / list.size() << endl;
            cout << "��߷֣�" << max << "����ͷ֣�" << min << endl;
            cout << "��߷�ID��" << endl;
            for (auto j = max_id.begin(); j != max_id.end(); j++)
                cout << *j << ' ';
            cout << endl << "��ͷ�ID��" << endl;
            for (auto j = min_id.begin(); j != min_id.end(); j++)
                cout << *j << ' ';
            cout << endl << string(32, '-') << endl << endl;
            cout << "����������˳�......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 3:
        {
            cout << "�ѽ���������ݱ����ģʽ" << endl;
            int id;
            cout << "������ѧ��ID��" << endl;
            cin >> id;
            auto list = info.GetStudentData(id);
            if (list.size() == 0)
            {
                cout << "ѧ�����޳ɼ���¼��ID�����������롣" << endl;
                system("pause");
                return 3;
            }
            cout << "���ݱ��ʽ��" << "�γ�ID ���� �ɼ�" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                cout << j->ID << ' ' << j->ClassPoint << ' ' << j->Point << endl;
            }
            cout << "����������˳�......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 4:
        {
            cout << "�ѽ���γ����ݱ����ģʽ" << endl;
            int id;
            cout << "������γ�ID��" << endl;
            cin >> id;
            auto _list = info.GetClassData(id);
            if (_list == nullptr)
            {
                cout << "�γ����޳ɼ���¼��ID�����������롣" << endl;
                system("pause");
                return 3;
            }
            auto list = _list->CountAverageBetween(-1, -1);
            cout << "���ݱ��ʽ��" << "ѧ��ID �ɼ�" << endl;
            for (auto j = list.begin(); j != list.end(); j++)
            {
                cout << j->first << ' ' << j->second << endl;
            }
            cout << "����������˳�......" << endl;
            cin.seekg(ios::end);
            cin.get();
            return 3;
            break;
        }
        case 5:
            return 0;
            break;
        default:
            throw "�޷�ʶ������кţ����������롣";
            break;
        }
    }
}