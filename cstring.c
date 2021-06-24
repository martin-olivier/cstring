#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CSTRING_DEBUG false

#if CSTRING_DEBUG
#define LOG(fn, txt) cstring_log(fn, txt)
#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"
void cstring_log(const char *function, const char *text)
{
    fprintf(stderr, YEL "[CSTRING WARNING]" RESET);
    fprintf(stderr, " -> ");
    fprintf(stderr, CYN "%s" RESET, function);
    fprintf(stderr, " -> ");
    fprintf(stderr, RED "%s\n" RESET, text);
}
#else
#define LOG(fn, txt)
#endif

void *cstring_alloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "[CSTRING] Bad Alloc, Abort...");
        exit(84);
    }
    return ptr;
}

static const size_t npos = -1;

typedef struct string_s
{
    char *data;
} string_t;

typedef string_t *string;

void string_assign(string dest, const char *src)
{
    if (src == NULL) {
        if (dest->data != NULL)
            free(dest->data);
        dest->data = NULL;
        return;
    }
    if (dest->data != NULL) {
        free(dest->data);
        dest->data = NULL;
    }
    dest->data = cstring_alloc(sizeof(char) * strlen(src) + 1);
    strcpy(dest->data, src);
}

string string_create(const char *str)
{
    string this = cstring_alloc(sizeof(string_t));
    this->data = NULL;
    string_assign(this, str);
    return this;
}

void string_copy(string dest, const string src)
{
    string_assign(dest, src->data);
}

string string_duplicate(const string this)
{
    return string_create(this->data);
}

void string_print(const string this)
{
    if (this->data == NULL) {
        fputs("(null)", stdout);
        return;
    }
    fputs(this->data, stdout);
}

void string_println(const string this)
{
    string_print(this);
    fputs("\n", stdout);
}

void string_clear(string this)
{
    string_assign(this, "");
}

const char *string_data(const string this)
{
    return this->data;
}

const char *string_c_str(const string this)
{
    return this->data;
}

size_t string_size(const string this)
{
    if (this->data == NULL) {
        LOG("string_size", "Tried to get the size of a NULL string (returned 0)");
        return 0;
    }
    return strlen(this->data);
}

size_t string_length(const string this)
{
    if (this->data == NULL) {
        LOG("string_length", "Tried to get the length of a NULL string (returned 0)");
        return 0;
    }
    return strlen(this->data);
}

int string_compare_c_str(const string this, const char *other)
{
    if (this->data == NULL && other == NULL) {
        LOG("string_compare, string_compare_c_str", "Tried to compare two strings with NULL content (returned 0)");
        return 0;
    }
    if (this->data == NULL || other == NULL) {
        LOG("string_compare, string_compare_c_str", "Tried to compare a standard string with a NULL string (returned -1)");
        return -1;
    }
    return strcmp(this->data, other);
}

int string_compare(const string this, const string other)
{
    return string_compare_c_str(this, other->data);
}

char string_at(const string this, size_t pos)
{
    if (this->data == NULL) {
        LOG("string_at", "Tried to reach the text on a NULL string (returned 0)");
        return 0;
    }
    if (pos >= string_length(this)) {
        LOG("string_at", "Tried to reach a position out of bounds (returned 0)");
        return 0;
    }
    return this->data[pos];
}

void string_push_back(string this, char insertion)
{
    char insertion_str[2];
    insertion_str[0] = insertion;
    insertion_str[1] = '\0';

    if (this->data == NULL)
        return string_assign(this, insertion_str);

    char *tmp = cstring_alloc(sizeof(char) * (string_length(this) + 2));
    strcpy(tmp, this->data);
    strcat(tmp, insertion_str);
    string_assign(this, tmp);
    free(tmp);
}

void string_pop_back(string this)
{
    size_t len = string_length(this);
    if (len == 0) {
        LOG("string_pop_back", "Tried to pop back an empty string (no changes)");
        return;
    }
    this->data[len - 1] = '\0';
}

void string_reverse(string this)
{
    if (this->data == NULL) {
        LOG("string_reverse", "Tried to reverse a NULL string (no changes)");
        return;
    }
    size_t i;
    size_t size = strlen(this->data);
    size_t j = size - 1;
    char temp;
    for (i = 0; i < size / 2; i++, j--) {
        temp = this->data[i];
        this->data[i] = this->data[j];
        this->data[j] = temp;
    }
    this->data[size] = '\0';
}

void string_swap(string this, string other)
{
    char *tmp = cstring_alloc(sizeof(char) * string_length(this) + 1);
    strcpy(tmp, this->data);

    string_assign(this, other->data);
    string_assign(other, tmp);

    free(tmp);
}

void string_cat(string this, const char *other)
{
    if (other == NULL) {
        LOG("string_cat, string_append", "Tried to concatenate a string with a NULL string (no changes)");
        return;
    }
    char *tmp = cstring_alloc(sizeof(char) * (string_length(this) + strlen(other) + 1));
    if (this->data == NULL) {
        string_assign(this, "");
        LOG("string_cat, string_append", "Tried to concatenate a NULL string with another string (this became other)");
    }
    strcpy(tmp, this->data);
    strcat(tmp, other);
    string_assign(this, tmp);
    free(tmp);
}

void string_append(string this, const string other)
{
    string_cat(this, other->data);
}

int string_file_get(string this, const char *path)
{
    int fd;
    struct stat buf;
    int size;
    char *str;

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        string_assign(this, NULL);
        return -1;
    }
    stat(path, &buf);
    size = buf.st_size;
    str = cstring_alloc(sizeof(char) * (size + 1));
    read(fd, str, size);
    str[size] = '\0';
    close(fd);
    string_assign(this, str);
    free(str);
    return 0;
}

int string_file_write(const string this, const char *path)
{
    if (this->data == NULL) {
        LOG("string_file_write", "Tried to write a NULL string to a file (returned -1)");
        return -1;
    }
    int fd = open(path, O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
        return -1;
    write(fd, this->data, string_length(this));
    close(fd);
    return 0;
}

int string_getline(string this)
{
    char buf = 0;
    string_clear(this);

    while (true) {
        buf = getchar();
        if (buf == -1)
            return -1;
        if (buf == '\n')
            break;
        string_push_back(this, buf);
    }
    return 0;
}

bool string_empty(const string this)
{
    if (this->data == NULL)
        return true;
    if (string_compare_c_str(this, "") == 0)
        return true;
    return false;
}

void string_destroy(string this)
{
    if (this->data != NULL)
        free(this->data);
    free(this);
    this = NULL;
}

size_t string_find_c_str(const string this, const char *to_find)
{
    char *res = strstr(this->data, to_find);
    if (!res)
        return npos;
    return res - this->data;
}

size_t string_find(const string this, const string to_find)
{
    return string_find_c_str(this, to_find->data);
}

char* cstring_strrstr(const char *haystack, const char *needle)
{
	char *r = NULL;

	if (!needle[0])
		return (char*)haystack + strlen(haystack);
	while (1) {
		char *p = strstr(haystack, needle);
		if (!p)
			return r;
		r = p;
		haystack = p + 1;
	}
}

size_t string_rfind_c_str(const string this, const char *to_find)
{
    char *res = cstring_strrstr(this->data, to_find);
    if (!res)
        return npos;
    return res - this->data;
}

size_t string_rfind(const string this, const string to_find)
{
    return string_rfind_c_str(this, to_find->data);
}

string string_substr(const string this, size_t pos, size_t len)
{
    string tmp = string_create("");
    for (size_t i = 0; pos < string_size(this) && i < len; i++, pos++)
        string_push_back(tmp, string_at(this, pos));
    return tmp;
}