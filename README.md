# cstring

[![cstring](https://img.shields.io/badge/cstring-v0.1-blue.svg)](https://github.com/tocola/cstring/releases/tag/v0.1)
[![MIT license](https://img.shields.io/badge/License-MIT-orange.svg)](https://github.com/tocola/cstring/blob/main/LICENSE)
![CPP Version](https://img.shields.io/badge/Language-C-darkgreen.svg)

[![GitHub watchers](https://img.shields.io/github/watchers/tocola/cstring?style=social)](https://github.com/tocola/cstring/watchers/)
[![GitHub forks](https://img.shields.io/github/forks/tocola/cstring?style=social)](https://github.com/tocola/cstring/network/members/)
[![GitHub stars](https://img.shields.io/github/stars/tocola/cstring?style=social)](https://github.com/tocola/cstring/stargazers/)

[![workflow](https://github.com/tocola/cstring/actions/workflows/unit_tests.yml/badge.svg)](https://github.com/tocola/cstring/actions/workflows/unit_tests.yml)
[![codecov](https://codecov.io/gh/tocola/cstring/branch/main/graph/badge.svg?token=4V6A9B7PII)](https://codecov.io/gh/tocola/cstring)

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
