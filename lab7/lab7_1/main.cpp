#include <iostream>

//nu stiu de ce nu merge daca pun altceva, cere neaparat double sau unsigned long long
float operator"" _Kelvin(unsigned long long kelvin) {
    return (float)(kelvin - 273.15);
}

float operator"" _Fahrenheit(unsigned long long fahrenheit) {
    return (float)((fahrenheit - 32) * 5.0 / 9.0);
}

int main() {
    float a = 300_Kelvin;
    float b = 120_Fahrenheit;

    std::cout << a << ' ' << b;
    return 0;
}