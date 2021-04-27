#include "parsers.h"
#include "lineNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int isSyntax(char c)
{
    return (c == '<' || c == '>' || c == '=' || c == '{' || c == '}');
}

void raiseSyntaxError(char c)
{
    printf("Unexpected character '%c' at line : %d", lineNumber);
    exit(1);
}

void parseType(FILE *fp, char dest[])
{
    //Reads the type of block,i.e, question and sample and stores it
    //in the char array passed in
    char c;              //for storing the character read
    flag inWord = false; //Flags if any character's been read
    int index = 0;       //Index for iterating over dest[] to store characters
    while ((c = fgetc(fp)))
    {
        if (!(isSyntax(c)) && !(c == ' ' || c == '{' || c == '\n')) //Check if given character is valid
        {
            inWord = true;
            dest[index] = c;
            index++;
        }
        else if (isSyntax(c) && c != '{') //Character part of syntax  and not '{'
        {
            raiseSyntaxError(c);
        }
        else if (inWord || c == '{') //Stop when ' ' comes after word or reads '{'
        {
            dest[index] = '\0';
            fseek(fp, -1L, SEEK_CUR); //set the cursor to prev cursor so it can be read
            break;                    //by other functions
        }
        if (c == '\n')
            lineNumber++;
    }
}

void parseArgument(FILE *fp, char parameter[], char value[])
{
    //Reads the parameter and its value, and stores them in the given array
    char c;               //For storing character read
    flag inParam = false; //Flags if parameter is being/been read
    flag inVal = false;   //Flags if value is being/been read
    flag escape = false;
    int index = 0;                 //index for filling the arrays
    while ((c = fgetc(fp)) != '{') //Move cursor to the start of argument
    {
        if (isSyntax(c) && c != '>')
        {
            raiseSyntaxError(c);
        }
        else if (c == '>') //Couldn't find a '{', No argument to read
        {
            strcpy(parameter, "NULL"); //return NULL in both if missing argument
            strcpy(value, "NULL");
            return;
        }

        if (c != ' ' && c != '\n') //Unexpected character
        {
            raiseSyntaxError(c);
        }
        if (c == '\n')
            lineNumber++;
    }
    while ((c = fgetc(fp))) //Get and fill parameter
    {
        if (!(isSyntax(c)) && !(c == ' ' || c == '\n')) //Fillin if valid char
        {
            inParam = true;
            parameter[index] = c;
            index++;
        }
        else if (isSyntax(c) && c != '=') //Raise syntax error if character is not '='
        {
            raiseSyntaxError(c);
        }
        else if (inParam) //space after parameter
        {
            parameter[index] = '\0';
            fseek(fp, -1L, SEEK_CUR);
            break;
        }
        if (c == '\n')
            lineNumber++;
    }
    index = 0;                     //reset index
    while ((c = fgetc(fp)) != '=') //Move cursor to '='
    {
        if (c == '}')
            ; //Raise error as '=' is expected
        {
            printf("Expected '=' in line number : %d", lineNumber);
            exit(1);
        }
        if (c != ' ' && c != '\n') //Excess character so raise syntax error
        {
            raiseSyntaxError(c);
        }
        if (c == '\n')
            lineNumber++;
    }
    while ((c = fgetc(fp))) //Fill in value after considering escape sequences
    {
        if (!escape && c == '}') //Unescaped '}' finishes the argument
        {
            value[index] = '\0';
            fseek(fp, -1L, SEEK_CUR);
            break;
        }
        else if (!escape && isSyntax(c)) //Unescaped syntax character raises error
        {
            raiseSyntaxError(c);
        }
        else if (c == '\\') // '\' escapes the next char
        {
            escape = true;
            inVal = true;
            continue;
        }
        else if (!(inVal) && (c == ' ' || c == '\n')) //Ignore all the spaces and newlines before first accepted character
        {
            continue;
        }
        else
        {
            value[index] = c; // The character is valid Thus fill it
            inVal = true;
            index++;
        }
        if (escape) //Toggle escape if true
            escape = false;
        if (c == '\n')
            lineNumber++;
    }
}