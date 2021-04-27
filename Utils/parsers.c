#include "parsers.h"
#include "lineNumber.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int isSyntax(char c)
{
    return (c == '<' || c == '>' || c == '=' || c == '{' || c == '}');
}


void parseType(FILE *fp,char dest[])
{
    //Reads the type of block,i.e, question and sample and stores it 
    //in the char array passed in
    char c;//for storing the character read
    flag inWord = false;//Flags if any character's been read
    int index = 0;//Index for iterating over dest[] to store characters
    while((c=fgetc(fp))!='{')
    {
        if(!(isSyntax(c)) && c!=' ')
        {
            inWord = true;
            dest[index] = c;
            index++;
        }
        else if (isSyntax(c))
        {
            printf("Unexpected symbol '%c' at line number : %d",c,lineNumber);
        }
        else if (inWord)//There's an ' ' so break here
        {
            dest[index] = '\0';
            fseek(fp,-1L,SEEK_CUR);//set the cursor to prev cursor so it can be read
            break;                 //by other functions
        }
        if (c == '\n') lineNumber++;
    }
}

void parseArgument(FILE *fp,char parameter[],char value[])
{
    //Reads the parameter and its value, and stores them in the given array
    char c;//For storing character read
    flag inParam = false;//Flags if parameter is being/been read
    flag inVal = false;//Flags if value is being/been read
    flag escape = false;
    int index = 0;//index for filling the arrays
    while ((c = fgetc(fp))!='{')//Move cursor to the start of argument
    {
        if (isSyntax(c) && c != '>')
        {
            printf("Unexpected char '%c' at line number : %d",c,lineNumber);
        }
        else if (c == '>')//Couldn't find a '{', No argument to read
        {
            strcpy(parameter,"NULL");//return NULL in both if missing argument
            strcpy(value,"NULL");
            return;
        }
        
        if (c != ' ' && c != '\n')
        {
            printf("Unexpected char '%c' at line number : %d",c,lineNumber);
            exit(1);
        }
        if (c == '\n') lineNumber++;
    }
    while ((c = fgetc(fp)))//Get and fill parameter
    {
        if (!(isSyntax(c)) && c != ' ')
        {
            inParam = true;
            parameter[index] = c;
            index++;
        }
        else if (isSyntax(c) && c!= '=')
        {
            printf("Unexpected char '%c' at line number : %d",c,lineNumber);
            exit(1);
        }
        else if (inParam)//space after parameter
        {
            parameter[index] = '\0';
            fseek(fp,-1L,SEEK_CUR);
            break;
        }
        if (c == '\n') lineNumber++;
    }
    index = 0;//reset index
    while ((c=fgetc(fp))!='=')//Move cursor to '='
    {
        if(c == '}');
        {
            printf("Expected '=' in line number : %d",lineNumber);
            exit(1);
        }
        if (c == '\n')lineNumber++;
        if (c != ' ' && c!='\n')
        {
            printf("Unexpected char '%c' at line number : %d",c,lineNumber);
            exit(1);
        }
    }
    while ((c = fgetc(fp)))//Fill in value after considering escape sequences
    {
        if(!escape && c == '}')
        {
            break;
        }
        else if (!escape && isSyntax(c))
        {
            printf("Unexpected char '%c' at line number : %d",c,lineNumber);
            exit(1);
        }
        else if(c == '\\')
        {
            escape = true;
            continue;
        }
        else
        {
            value[index] = c;
            index++;
        }
        if (escape) escape = false;
        if (c == '\n') lineNumber++;
    }
}