#include <iostream>
#include <strstream>
#include "Displayer.h"

using namespace std;

namespace Displayer
{
    int Cover()
    {
        cout << "����һ�����档" << endl;

        auto a = "E:\\\nStudent.dat\n10254 Math 3";
        auto s = istrstream(a);


        Structure::ClassInfo classInfo(s);

        return 0;
    }
}