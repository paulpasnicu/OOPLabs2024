#include <iostream>

using namespace std;

int stringLength(char s[100])
{
    int lg = 0;
    while (s[lg]!=NULL) lg++;
    return lg;
}
int convertNumar(char s[100])
{
    int number = 0;
    for (i=0; i<lg; i++)
        number = number*10 + (s[i]-'0');
}
int main()
{
    FILE *citire;
    char numar[100];
    int suma=0;
    citire=fopen("in.txt","r");
    while(fgets(numar, stringLength(numar), citire)!=NULL)
    {
        suma+=convertNumar(numar);
    }
    printf("%d", suma);
    fclose(citire);
    return 0;
}
