#include "cleanText.h"

void clean(char text[])
{
    int i = 0;
    int j = 0;
    while (text[i]!='\0')
    {
        if (text[i]=='\\')
        {
            i++;
            continue;
        }
        text[j] = text[i];
        i++;
        j++;
    }
    text[j] = '\0';
}

int splitOptions(char* dest[],char input[])
{
    //do this with vectors
}