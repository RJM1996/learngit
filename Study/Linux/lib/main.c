#include <stdio.h>
#include "add.h"
#include "sub.h"
#include "chengfa.h"
#include "div.h"

int main()
{
    int a = 9;
    int b = 3;
    printf("add = %d\n", add(a, b));
    printf("sub = %d\n", sub(a, b));
    printf("chengfa = %d\n", chengfa(a, b));
    printf("div = %d\n", div(a, b));
    return 0;
}
