#include <stdio.h>
#include <glad/glad.h>

void getErrorAndLog(const char* file, const int line);

#define checkError() getErrorAndLog(__FILE__, __LINE__)
