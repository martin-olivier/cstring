# cstring
The goal of this project is to recreate the `string` class of the C++ standard library in C. Syntax changes will be forced due to the absence of classes in C :
```c++
// in C++
std::string str = "Hello";
str.push_back(' ');
str += "World";

// in C with cstring
string str = string_create("Hello");
string_push_back(str, ' ');
string_cat(str, "World");
string_destroy(str);
```

# Example

```c++
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
```