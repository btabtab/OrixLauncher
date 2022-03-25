#include <stdio.h>
#include <inttypes.h>

#include "ToasterDSP.h"
#include "../Saving.h"
#include "../../Jlib/Text_input_Handling_System.h"
#include "../../Jlib/TEXT_COL_CODES.h"

#define FANCY_PRINTING_VAL 32
int main()
{
	uint32_t* data;
	int data_size = 44144;
	data = malloc(data_size);
	loadData(data, data_size, "conv.wav");
	system("cls");
	printf("start of program<3\n\n");
	printf("{\n");
	for(int i = 0; i != data_size; i++)
	{
	}
	printf("\n};");
	return 0;
}