#include "../cstring.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    string i = string_create("hello");
    string_push_back(i, ' ');
    string_cat(i, "world!");
    string_println(i);
    string_destroy(i);
    return 0;
}