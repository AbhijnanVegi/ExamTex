#include "cleanText.h"
#include<stdlib.h>
#include<string.h>

void remove_spaces(char **c)
{
    int len = strlen(*c);
    char *x = (char *)malloc(sizeof(char) * len + 1);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if ((*c)[i] == ' ' || (*c)[i] == '\n')
            continue;
        break;
    }
    int j = 0;
    for (j = len - 1; j >= 0; j--)
    {
        if ((*c)[j] == ' ' || (*c)[j] == '\n')
        {
            (*c)[j] = '\0';
        }
        else
            break;
    }
    strcpy(x, &((*c)[i]));
    strcpy(*c, x);
    if (strlen(*c)!=strlen(x)) *c = (char *)realloc(*c, strlen(x) + 1);
    free(x);
}

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