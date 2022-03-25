/*
This is the file handling managment module
from the Jlib library.
*/
#ifndef JLIB_FILE_HANDLING_MODULE
#define JLIB_FILE_HANDLING_MODULE
#include <stdlib.h>
#include <stdio.h>
/*
This is the home of the current file pointer.
*/
FILE** getCurrentFilePointer()
{
	static FILE* current_file = NULL;
	// if(!current_file){exit(0);}
	return &current_file;
}
//opens the file into the pointer.
void openCurrentFileAsBinary(const char* file_name)
{
	*(getCurrentFilePointer()) = fopen(file_name, "rb+");
}

void closeCurrentFile()
{
	fclose(*getCurrentFilePointer());
}

void readFromFileAsBinary(void* buffer, size_t element_size, size_t element_count)
{
	fread(buffer, element_size, element_count, *(getCurrentFilePointer()));
}

void WriteToFileAsBinary(void* buffer, size_t element_size, size_t element_count)
{
	fwrite(buffer, element_size, element_count, *(getCurrentFilePointer()));
}
#endif