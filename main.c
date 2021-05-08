#include <stdio.h>
#include "vector/vec.h"
#include "Utils/cleanText.h"
#include "Utils/lineNumber.h"
#include "Utils/parsers.h"
#include "Utils/readFile.h"
#include <stdlib.h>
int main()
{
    vector v = allocate(CHARSTACK, 2);
    parameterUnion temp;
    temp.cs.ch = 'j';
    temp.cs.lineno = 1;
    temp.cs.colno = 234;
    push_back(&v, temp);
    parameterUnion t = back(v);
    printf("%c %d %d\n", t.cs.ch, t.cs.lineno, t.cs.colno);

    float a = atof(" 1 2");
    printf("%f", a);

    return 0;
}