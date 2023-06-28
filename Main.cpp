#include <iostream>
#include "Displayer.h"

int main()
{
    // 操作的分支id
    // 0：封面打印；1：录入功能；2：修改功能；3：查询功能；4：统计功能
    int branch = 0;

    Displayer::Cover();

    system("pause");
    return 0;
}