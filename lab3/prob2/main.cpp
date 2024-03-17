#include <iostream>
#include "Canvas.h"

using namespace std;
int main()
{
    Canvas Canvas;
    Canvas.Clear();

    Canvas.DrawCircle(15, 15, 15, '*');
    Canvas.FillCircle(15, 15, 15, '-');
    Canvas.Print();
    Canvas.Clear();

    Canvas.DrawRect(15, 15, 35, 35, '*');
    Canvas.FillRect(15, 16, 35, 35, '-');
    Canvas.Print();
    Canvas.Clear();

    Canvas.SetPoint(15, 35, '*');
    Canvas.SetPoint(40, 50, '*');
    Canvas.DrawLine(15, 35, 40, 50, '-');
}
