#include "../cstring.h"
#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(cstring, basic)
{
    string i = string_create("hello");
    string_push_back(i, ' ');
    string_cat(i, "world!");
    cr_assert_str_eq(string_data(i), "hello world!");
    string_destroy(i);
}