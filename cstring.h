#pragma once

#include <stdbool.h>
#include <stddef.h>

static const size_t npos = -1;

typedef struct string_t *string;

/**
 *  Change the value of a <string> object from a <char *>
 */
void string_set(string dest, const char *src);
/**
 *  Change the value of a <string> object from another <string> object
 */
void string_copy(string dest, const string src);
/**
 *  Duplicate a string into a new alloced one
 *  @param this string to be duplicate.
 *  @returns string with a new adress with the same content as the string in parameter
 */
string string_duplicate(const string this);
/**
 *  Print the current value of a <string> object
 */
void string_print(const string this);
/**
 *  Print the current value of a <string> object followed by an endline
 */
void string_println(const string this);
/**
 *  Clear a <string> object
 */
void string_clear(string this);
/**
 *  Return the current value of a <string> object as a <const char *>
 */
const char *string_data(const string this);
/**
 *  Return the current value of a <string> object as a <const char *>
 */
const char *string_c_str(const string this);
/**
 *  Return the size of the current value of a <string> object
 */
size_t string_size(const string this);
/**
 *  Return the lenght of the current value of a <string> object
 */
size_t string_length(const string this);
/**
 *  Compare a <string> and a <char *>. the result is the same as strcmp()
 */
int string_compare_c_str(const string this, const char *other);
/**
 *  Compare two <string> objects. the result is the same as strcmp()
 */
int string_compare(const string this, const string other);
/**
 *  Return the <char> located at this[pos]
 */
char string_at(const string this, size_t pos);
/**
 *  Add a <char> at the end of a <string> object
 */
void string_push_back(string this, char insertion);
/**
 *  Remove the last <char> of a <string> object
 */
void string_pop_back(string this);
/**
 *  Reverse the entire <string>
 */
void string_reverse(string this);
/**
 *  Swap the content of two <string> objects
 */
void string_swap(string this, string other);
/**
 *  Concatenate the value of a <string> object and a <char *>
 */
void string_cat(string this, const char *other);
/**
 *  Add the value of "new_string" at the end of "this"
 *  (Use string_cat to concatenate a <string> with a <char *>)
 */
void string_append(string this, const string other);
/**
 *  Store the content of a file in the string.
 *  The content of the string will be replaced
 *  @param this string that will get the file content.
 *  @param path path to the file.
 *  @returns -1 if opening the file failed (the string will remain the same), 0 otherwise.
 */
int string_file_get(string this, const char *path);
/**
 *  Write the string's data in a file specified by a path. 
 *  The content of the file will be replaced
 *  @param this string where the data to write is contain.
 *  @param path path to the file where the content of the string will be written.
 *  @returns -1 if opening / creating the file failed, 0 otherwise.
 */
int string_file_write(const string this, const char *path);
/**
 *  Creates a <string> object with the content of <str>
 *  @param str content that will be stored by the <string>
 *  @returns a new string
 */
string string_create(const char *str);
/**
 *  Destroy a <string> object
 *  @param this string to be destroyed
 */
void string_destroy(string this);
/**
 *  Wait for user input and store input in <this>
 *  @param this string where the content of getline will be stored.
 *  @returns -1 if EOF / 0 otherwise.
 */
int string_getline(string this);
/**
 *  @param this string struct
 *  @returns true if the string is empty / false otherwise.
 */
bool string_empty(const string this);
/**
 *  Searches the string for the first occurrence of the sequence specified by its arguments.
 *  @param to_find A c_string with the subject to search for.
 *  @returns The position of the first character of the first match.
 */
size_t string_find_c_str(const string this, const char *to_find);
/**
 *  Searches the string for the first occurrence of the sequence specified by its arguments.
 *  @param to_find Another string with the subject to search for.
 *  @returns The position of the first character of the first match.
 */
size_t string_find(const string this, const string to_find);
/**
 *  Searches the string for the last occurrence of the sequence specified by its arguments.
 *  @param to_find A c_string with the subject to search for.
 *  @returns The position of the first character of the last match.
 */
size_t string_rfind_c_str(const string this, const char *to_find);
/**
 *  Searches the string for the last occurrence of the sequence specified by its arguments.
 *  @param to_find Another string with the subject to search for.
 *  @returns The position of the first character of the last match.
 */
size_t string_rfind(const string this, const string to_find);
/**
 *  Returns a newly constructed string object with its value initialized to a copy of a substring of this object
 *  @param pos Position of the first character to be copied as a substring
 *  @param len Number of characters to include in the substring (npos indicates all characters until the end of the string)
 *  @returns A string object with a substring of this object
 */
string string_substr(const string this, size_t pos, size_t len);