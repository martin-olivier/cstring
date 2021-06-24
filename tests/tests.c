#include "../cstring.h"
#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>

Test(cstring, hello_world_test)
{
    string str = string_create("hello");
    string_push_back(str, ' ');
    string_cat(str, "world!");
    cr_assert_str_eq(string_data(str), "hello world!");
    string_destroy(str);
}

Test(cstring, string_assign_test)
{
    string str = string_create("");
    string_assign(str, NULL);
    cr_assert_eq(string_data(str), NULL);
    string_assign(str, "test_string");
    cr_assert_str_eq(string_data(str), "test_string");
    string_destroy(str);
}

Test(cstring, string_copy_test)
{
    string src = string_create("abc");
    string dest = string_create("xyz");
    string_copy(dest, src);
    cr_assert_str_eq(string_data(dest), "abc");
    string_destroy(src);
    string_destroy(dest);
}

Test(cstring, string_duplicate_test)
{
    string str = string_create("STRDUP");
    string newstr = string_duplicate(str);
    cr_assert_str_eq(string_data(newstr), "STRDUP");
    string_destroy(str);
    string_destroy(newstr);
}

Test(cstring, string_print_test)
{
    string str = string_create("content");
    string other = string_create(NULL);
    freopen("test_print.txt", "w", stdout);
    string_println(str);
    string_println(other);
    fclose(stdout);
    if (string_file_get(other, "test_print.txt") == -1)
        cr_assert_eq(true, false);
    cr_assert_str_eq(string_data(other), "content\n(null)\n");
    string_destroy(str);
    string_destroy(other);
}

Test(cstring, string_clear_test)
{
    string str = string_create(NULL);
    string_clear(str);
    cr_assert_str_eq(string_data(str), "");
    string_assign(str, "fill");
    string_clear(str);
    cr_assert_str_eq(string_c_str(str), "");
    string_destroy(str);
}

Test(cstring, string_size_test)
{
    string str = string_create(NULL);
    cr_assert_eq(string_size(str), 0);
    string_assign(str, "");
    cr_assert_eq(string_length(str), 0);
    string_assign(str, "abcdef");
    cr_assert_eq(string_size(str), 6);
    string_destroy(str);
}

Test(cstring, string_cmp_test)
{
    string str = string_create(NULL);
    cr_assert_eq(string_compare_c_str(str, NULL), 0);
    cr_assert_eq(string_compare_c_str(str, "abc"), -1);
    string_assign(str, "abc");
    string other = string_create("def");
    cr_assert_neq(string_compare(str, other), 0);
    string_destroy(str);
    string_destroy(other);
}

Test(cstring, string_at_test)
{
    string str = string_create(NULL);
    cr_assert_eq(string_at(str, 2), 0);
    string_assign(str, "abc");
    cr_assert_eq(string_at(str, 20), 0);
    cr_assert_eq(string_at(str, 2), 'c');
    string_destroy(str);
}

Test(cstring, string_push_back_test)
{
    string str = string_create(NULL);
    string_push_back(str, 'a');
    string_push_back(str, 'b');
    string_push_back(str, 'c');
    cr_assert_str_eq(string_data(str), "abc");
    string_destroy(str);
}

Test(cstring, string_pop_back_test)
{
    string str = string_create(NULL);
    string_pop_back(str);
    string_push_back(str, 'a');
    string_push_back(str, 'b');
    string_push_back(str, 'c');
    string_pop_back(str);
    string_pop_back(str);
    cr_assert_str_eq(string_data(str), "a");
    string_destroy(str);
}

Test(cstring, string_reverse_test)
{
    string str = string_create(NULL);
    string_reverse(str);
    cr_assert_eq(string_data(str), 0);
    string_assign(str, "abc");
    string_reverse(str);
    cr_assert_str_eq(string_data(str), "cba");
    string_assign(str, "abcd");
    string_reverse(str);
    cr_assert_str_eq(string_data(str), "dcba");
    string_destroy(str);
}

Test(cstring, string_swap_test)
{
    string str = string_create("str");
    string other = string_create("other");
    string_swap(str, other);
    cr_assert_str_eq(string_data(str), "other");
    cr_assert_str_eq(string_data(other), "str");
    string_destroy(str);
}

Test(cstring, string_cat_append_test)
{
    string str = string_create(NULL);
    string other = string_create("def");
    string_cat(str, "abc");
    string_cat(str, NULL);
    string_append(str, other);
    cr_assert_str_eq(string_data(str), "abcdef");
    string_destroy(str);
    string_destroy(other);
}

Test(cstring, string_file_test)
{
    string str = string_create("content");
    if (string_file_get(str, "bad.txt") != -1)
        cr_assert_eq(true, false);
    if (string_file_write(str, "test_file.txt") != -1)
        cr_assert_eq(true, false);
    string_assign(str, "content");
    if (string_file_write(str, "test_file.txt") == -1)
        cr_assert_eq(true, false);
    if (string_file_get(str, "test_file.txt") == -1)
        cr_assert_eq(true, false);
    cr_assert_str_eq(string_data(str), "content");
    string_destroy(str);
}

Test(cstring, string_empty_test)
{
    string str = string_create(NULL);
    cr_assert_eq(string_empty(str), true);
    string_assign(str, "");
    cr_assert_eq(string_empty(str), true);
    string_assign(str, "a");
    cr_assert_eq(string_empty(str), false);
    string_destroy(str);
}

Test(cstring, string_find_test)
{
    string str = string_create("hello world!");
    string other = string_create("hello");
    cr_assert_eq(string_find(str, other), 0);
    cr_assert_eq(string_find_c_str(str, "o wo"), 4);
    cr_assert_eq(string_find_c_str(str, "abc"), npos);
    string_destroy(str);
    string_destroy(other);
}

Test(cstring, string_rfind_test)
{
    string str = string_create("abcababcd");
    string other = string_create("ab");
    cr_assert_eq(string_rfind(str, other), 5);
    cr_assert_eq(string_rfind_c_str(str, ""), 9);
    cr_assert_eq(string_rfind_c_str(str, "c"), 7);
    cr_assert_eq(string_rfind_c_str(str, "abca"), 0);
    cr_assert_eq(string_rfind_c_str(str, "zabca"), npos);
    string_destroy(str);
    string_destroy(other);
}

Test(cstring, string_substr_test)
{
    string str = string_create("abcdefghi");
    string o1 = string_substr(str, 3, npos);
    cr_assert_str_eq(string_data(o1), "defghi");
    string o2 = string_substr(str, 3, 0);
    cr_assert_str_eq(string_data(o2), "");
    string o3 = string_substr(str, 3, 2);
    cr_assert_str_eq(string_data(o3), "de");
    string o4 = string_substr(str, npos, npos);
    cr_assert_str_eq(string_data(o4), "");
    string_destroy(str);
    string_destroy(o1);
    string_destroy(o2);
    string_destroy(o3);
    string_destroy(o4);
}