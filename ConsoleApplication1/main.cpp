// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SNcal.h"

using namespace std;

int main()
{
    SNCalc SN4(4);
    SN4.Geoinit(100, 100);
    SN4.Matinit(0.25, 0.15, 0.01, 0.0025);
    SN4.Sourceinit(1e3, 0, 25, 25, 50);
    SN4.Calc(12, 12);
    
}

