#include <iostream>
#include <strstream>
#include "..\Include\Displayer.h"

using namespace Structure;
using namespace std;

namespace Displayer
{
    int Cover(Structure::ClassInfo& info)
    {
        cout << string(32, '+') << endl << endl
            << "       ѧ���ɼ�����ϵͳ        " << endl << endl
            << string(32, '#') << endl << endl
            << "           ���˵�             " << endl << endl
            << "         1. ¼��ϵͳ          " << endl
            << "         2. �޸�ϵͳ          " << endl
            << "         3. ��ѯϵͳ          " << endl
            << "         4. ͳ��ϵͳ          " << endl
            << "         5. �˳�ϵͳ          " << endl << endl
            << string(32, '#') << endl << endl;
        cout << "������ָ��ǰ������ѡ�";
        int i = 0;
        cin >> i;
        if (cin.fail())
            throw "���Ϸ����������ݣ�����������";
        switch (i) {
        case 1:
            cout << "��������¼��ϵͳ......" << endl;
            return 1;
        case 2:
            cout << "���������޸�ϵͳ......" << endl;
            return 2;
        case 3:
            cout << "���������ѯϵͳ......" << endl;
            return 3;
        case 4:
            cout << "��������ͳ��ϵͳ......" << endl;
            return 4;
        case 5:
            cout << "�Ƿ�ȷ���˳�(y/n)��" << endl;
            cin.seekg(ios::end);
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
                return -1;
            else
                return 0;
            break;
        default:
            throw "�޷�ʶ������кţ����������롣";
            break;
        }



        
        ClassInfo cInfo("E:\\bin\\");
        auto c = cInfo.GetClassData(1001);
        c->UpdateStudentData(3, 80);
        cInfo.UpdateClassData(*c);
        auto ss = cInfo.GetStudentData(1);
        cInfo.SaveClassInfo();

        return 0;
    }
}