#include <iostream>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Input(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       ѧ���ɼ�����ϵͳ        " << endl
            << "           ¼��ϵͳ           " << endl << endl
            << string(32, '#') << endl << endl
            << "      1.ͨ���ļ�·��¼��       " << endl
            << "         2. �ֶ�¼��          " << endl
            << "         3. ֹͣ¼��          " << endl
            << string(32, '#') << endl << endl;
        cout << "������ָ��ǰ������ѡ�";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        switch (i)
        {
        case 1:
        {
            cout << "�ѽ����ļ�·������ģʽ��" << endl;
            cout << "�������ļ�·����" << endl;
            char path[256];
            cin.seekg(ios::end);
            cin.getline(path, 256);
            ifstream file(path);
            if (!file.is_open())
                throw "���Ϸ����ļ�·����";
            int id, point;
            string name;
            file >> id >> name >> point;
            Structure::ClassData data(id, name, point);
            data.ReadFromStream(file);
            info.UpdateClassData(data);
            cout << "����¼����ϡ�";
            sleep(2000);
            return 1;
            break;
        }
        case 2:
        {
            cout << "�ѽ����ֶ�¼��ģʽ��" << endl;
            cout << "������γ���ţ�" << endl;
            int id, point;
            cin >> id;
            cout << "������γ�����(�޿ո�)��" << endl;
            string name;
            cin >> name;
            cout << "������γ̼��㣺" << endl;
            cin >> point;
            Structure::ClassData data(id, name, point);
            int stuId = 0, score = 0;
            cout << "��ѭ������ѧ��ѧ��+ѧ���ɼ������븺���˳���" << endl;
            while (true)
            {
                cin >> stuId;
                if (stuId < 0) break;
                cin >> score;
                if (score < 0) break;
                if (cin.fail())
                {
                    cout << "����������ı������������롣" << endl;
                    cin.clear(), cin.seekg(ios::end);
                }
                data.UpdateStudentData(stuId, point);
            }
            info.UpdateClassData(data);
            cout << "����¼����ϡ�";
            sleep(2000);
            return 1;
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