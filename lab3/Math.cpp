#include <cstring>
#include <cstdarg>
#include "Math.h"

int v[100];

int max(int a, int b)
{
    if (a>b) return a;
    return b;
}
int Math::Add(int x, int y)
{
	return x + y;
}

int Math::Add(int x, int y, int z)
{
	return x + y + z;
}

int Math::Add(double x, double y)
{
	return x + y;
}

int Math::Add(double x, double y, double z)
{
	return x + y + z;
}

int Math::Mul(int x, int y)
{
	return x * y;
}

int Math::Mul(int x, int y, int z)
{
	return x * y * z;
}

int Math::Mul(double x, double y)
{
	return x * y;
}

int Math::Mul(double x, double y, double z)
{
	return x * y * z;
}

int Math::Add(int count, ...)
{
	va_list args;
	va_start(args, count);
	int rez = 0;
	while (count != 0)
	{
		int elem = va_arg(args, int);
		rez = rez + elem;
		count--;
	}
	va_end(args);
	return rez;
}

char* Add(const char* a, const char* b)
{
	int newN = max(strlen(a), strlen(b))+1, rez=0, t=0;
    char rezultat[newN];
    for (int i = newN-1; i>=0; i++)
    {
        rez=(a[i]-'0'+b[i]-'0')+t;
        if (rez>10)
        {
            rez=rez%10;
            t=rez/10;
        }
        else t=0;
        rezultat[i]=(rez+'0');
    }
}