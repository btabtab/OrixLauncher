#ifndef SAVE_FUNCTIONS
#define SAVE_FUNCTIONS
#include <stdio.h>

/*
Probably my favorite set of functions, it just makes
anything to do with saving files from tools to be used in main software so much easier.
*/

void saveData(void* buffer, int size, char* filename)
{
	FILE* file = fopen(filename, "wb");
	fwrite(buffer, size, 1, file);
	fclose(file);
}

void loadData(void* buffer, int size, char* filename)
{
	FILE* file = fopen(filename, "rb");
	fread(buffer, size, 1, file);
	fclose(file);
}

void saveTextFile(void* buffer, int size, char* filename)
{
	FILE* file = fopen(filename, "w");
	fwrite(buffer, size, 1, file);
	fclose(file);
}
#endif