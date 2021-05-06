#include <stdio.h>
#include "vec.h"
#include <stdlib.h>
int main()
{
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Please use the functions given as much as possible and 
    //manually look for things inside the vector only when absolutely necessary
    //I will be adding error handling (if time permits to all the functions) 
    


    //================================================================================================================
    //   WORKING WITH STRINGS
    // add_string function adds string behind the current string
    // on using add_string "hel"+ "lo" ="hello"
    //cpy_string deletes the previous string and copies teh new string
    // on using cp_string "hel" + "lo" = "lo"
    //If you want to acces the string use return_string function which returns a char* for the string

    vector str = allocate(STRING, 50); // allocation of string
    char c[10];                        // char array which we need to add to the string
    strcpy(c, "hel");
    add_string(&str, &c[0]); // we need to pass the pointer to the vector and the cahr * to the func
    //str = "hel"
    strcpy(c, "lo");
    add_string(&str, &c[0]);
    //str = "hello"
    cpy_string(&str, &c[0]);
    //str = "lo"
    char *x = return_string(&str);
    //x[0] = 'l' and so on x can be used for random acces of the string
    //x = "lo"
    //Please don't use push_back, pop_back, back and front functions for string
    // they don't make any sense and hance are not implemented
    //==============================================================================================================
    //  WORKING WITH CHARACTER STACK
    //  To be used for balancing brackets
    vector stack = allocate(CHARSTACK, 20);
    //For passing anything to the stack we need to pass it as a union
    parameterUnion temp;
    temp.cs.ch = 'j'; //the char of the stack struct
    //cs refers to character stack and ch means character
    temp.cs.lineno = 1; // cs refers to character  stack and lineno refers to lineno
    temp.cs.colno = 234;
    push_back(&v, temp);        // pass the pointer and the union in the functions
    parameterUnion t = back(v); // back and front return the last and first element in the stack in the form of union
    // Please be very careful on what the union contains (stack or node) you can use stack.elementType to check the elementType of the vector
    pop_back(&stack); //pops the alst element from the stack
    printf("%c %d %d\n", t.cs.ch, t.cs.lineno, t.cs.colno);

    //   =========================================================================================================================
    // WORKING WITH NODE
    // To be used for storing the actual difficulty, lineno and score for each question

    vector node = allocate(NODE, 20);
    //again for passing anything we need to storre it in a union first
    parameterUnion temp2;
    temp2.nd.diff = 1.2;  //stores the difficulty of the question nd stands for node
    temp2.nd.score = 2.5; // stores the score of the question
    temp2.nd.id = 23;     //stores the token for the ftell and fseek functions
    // For random access in the node array use
    node.u.nodeElems[i]; //node is the name of the vector u is for the union of pointers nodeElems is for the array
    //and i is the ith elemenet
    //to pass it into a function for sorting or smthing else where it takes input as struct array use
    sort(&node.u.nodeElems[0],node.last);
    //assuming the funstion is difined as sort(node*array,int number_of_elements)
    return 0;
}