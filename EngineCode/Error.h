#ifndef ERROR
#define ERROR
#include <stdio.h>

typedef struct Error
{
    int code;
}
Error;

void dumpLog(char* input_buffer)
{
	char dump_buffer[120] = "";
	sprintf(dump_buffer, input_buffer);
	// saveData("dump.txt", 90, dump_buffer);
}

void throwErrorWithMessage(char* error_message)
{
    // saveData(error_message, 120, "thrown error data.txt");
}
#endif