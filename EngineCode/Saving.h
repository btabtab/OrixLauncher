#ifndef SAVE_FUNCTIONS
#define SAVE_FUNCTIONS
#include <stdio.h>
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