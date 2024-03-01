#include <iostream>

using namespace std;

int main()
{
    char cuvinte[256][256], sir[256], *p;
    int nr=0;
    scanf("%[^\n]", sir);
    p=strtok(sir, " ");
    while(p!=NULL)
    {
        strcpy(cuvinte[nr], p);
        nr++;
        p=strtok(NULL, " ");
    }
    for(int i=0; i<nr-1; i++)
    {
        for(int j=i+1; j<nr; j++)
        {
            if(strlen(cuvinte[i])<strlen(cuvinte[j])) ///ordoneaza descrescator dupa lungimea sirului
            {
                swap(cuvinte[i], cuvinte[j]);
            }
            if(strlen(cuvinte[i])==strlen(cuvinte[j])) ///cazul cand doua cuvinte au aceeasi lungime
            {
                if(strcmp(cuvinte[i], cuvinte[j])>0) ///daca nu sunt ordonate alfabetic
                {
                    swap(cuvinte[i], cuvinte[j]);
                }
            }
        }
    }
    for(int i=0; i<nr; i++)
    {
        printf("%s \n", cuvinte[i]);
    }
    return 0;
}
