/*
This whole file should become a big thing that can be used to
help handle user input in a more versatile and friendly way than
the standard library can offer usually.
*/
#ifndef TIHS
#define TIHS
#include <stdio.h>
#include <stdlib.h>

#define JL_BUFFER_LENGTH 30

#define NO_VALIDATION 0x0000
#define INTEGER_VALIDATION 0x0001
#define FLOAT_VALIDATION 0x0002
#define NAME_VALIDATION 0x0003
#define AGE_VALIDATION 0x0004

/*
Runs a check on the validation of the entered text
returns:
	"0" if failed.
	"1" if passed.
*/
int runValidationCheck(char* buffer, int type)
{
	int i = 0;
	switch (type)
	{
	case NAME_VALIDATION:
		for(i = 0; i != JL_BUFFER_LENGTH; i++)
		{
			if(buffer[i] > '0' && buffer[i] < '9')
			{
			}
		}
		break;
	
	default:
		break;
	}
}

void* grabTextFromConsole()
{
	//This is the input buffer.
	static char buffer[30] = "";
	//This scans for terminal input, fgets accepts spaces.
	fgets(buffer, 30, stdin);

	//returns the pointer to the buffer.
	return buffer;
}
#define graTeFroCon grabTextFromConsole

/*
This just makes grabbing text from the user so much
easier than having to make a new buffer for printf
every single time.
comes with validation.
(validation codes)
NO_VALIDATION
INTEGER_VALIDATION
FLOAT_VALIDATION
NAME_VALIDATION
AGE_VALIDATION
*/
void* grabTextFromConsoleWithValidation(int validation_type)
{
	//This is the input buffer.
	static char buffer[JL_BUFFER_LENGTH] = "";
	//This scans for terminal input, fgets accepts spaces.
	fgets(buffer, JL_BUFFER_LENGTH, stdin);
	runValidationCheck(buffer, validation_type);
	//returns the pointer to the buffer.
	return buffer;
}
#endif