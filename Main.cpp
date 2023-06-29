#include <iostream>
#include "Displayer.h"

using namespace std;
using namespace Displayer;

int main()
{
    Structure::ClassInfo info("E:\\bin\\");
    // 操作的分支id
    // 0：封面打印；1：录入功能；2：修改功能；3：查询功能；4：统计功能
    int branch = 0;

    while (branch >= 0)
    {
        try
        {
            switch (branch)
            {
            case 0:
                branch = Cover(info);
                break;
            case 1:
                branch = Input(info);
                break;
            case 2:
                branch = Modify(info);
                break;
            case 3:
                branch = Search(info);
                break;
            case 4:
                branch = Count(info);
                break;
            default:
                info.SaveClassInfo();
            }
        }
        catch (const char* Exception)
        {
            cout << "Fatal Error: " << endl << Exception << endl;
            cin.seekg(ios::end);
            while (!cin)
            {
                cin.clear();
                while (cin.get() != '\n')
                    continue;
            }
            sleep(2000);
        }
        std::system("cls");
    }
    return 0;
}