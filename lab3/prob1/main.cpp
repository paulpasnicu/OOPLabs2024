// Problema 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Write a class in C++ that has the following definition:

class Math
{
public:
    static int Add(int,int);
    static int Add(int,int,int);
    static int Add(double,double);
    static int Add(double,double,double);
    static int Mul(int,int);
    static int Mul(int,int,int);
    static int Mul(double,double);
    static int Mul(double,double,double);
    static int Add(int count,...); // sums up a list of integers
    static char* Add(const char *, const char *)
}

Organize the code in the following way:
- a header file called Math.h
- a cpp file called Math.cpp that contains the source code for class Math
- a main file called main.cpp that contains the main function and has an example on how to use Math. 
The example must include using all methods from the class.
- for the variadic method use pointers or va_start / va_end macros.
- Add(const char *, const char *) will allocate memory that can add the two existing string. 
If one of the strings is nullptr, this function will return nullptr;
*/

#include <iostream>
#include "Math.h"

using namespace std;

int main()
{
    Math calc;
    int xi, yi, zi;
    double xd, yd, zd;
    const char a = 'a', b = 'b';
    int count, v[100];

    cin >> xi >> yi >> zi >> xd >> yd >> zd;

    cout << calc.Add(xi, yi) << calc.Add(xi, yi, zi) << calc.Add(xd, yd) << calc.Add(xd, yd, zd) << endl;
    cout << calc.Mul(xi, yi) << calc.Mul(xi, yi, zi) << calc.Mul(xd, yd) << calc.Mul(xd, yd, zd) << endl;
    cout << calc.Add(4, 1, 2, 3, 4) << endl;
    cout << calc.Add(a, b);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
