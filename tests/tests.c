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

Test(string_find_test, basic)
{
    string str = string_create("hello world!");
    string other = string_create("hello");
    size_t res = string_find(str, other);
    printf("%zu\n", res);
    cr_assert_eq(res, 0);
    string_destroy(str);
    string_destroy(other);
}