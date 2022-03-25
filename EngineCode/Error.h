#ifndef ERROR
#define ERROR
#include <stdio.h>

typedef struct Error
{
    int code;
}
Error;

void saveData(char* buffer, char* filename)
{
	FILE* file = fopen(filename, "w");
    fputs(buffer, file);
	fclose(file);
}

void throwErrorWithMessage(char* error_message)
{
    saveData(error_message, "ErrorDump.txt");
}
#endif