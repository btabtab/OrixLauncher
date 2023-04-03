#ifndef KETTLE_STRING
#define KETTLE_STRING

#define KETTLE_STRING_LENGTH 60

#include <stdio.h>
#include <raylib.h>

/*
Kettle string is a struct that is supposed to handle
storing and generalising strings such that the user
of this library needn't worry about string issues
complexities.
*/

typedef struct KettleString
{
	char contents[KETTLE_STRING_LENGTH];
}
KettleString;

//erases the contents of a kettle string.
void clearKettleString(KettleString* label)
{
	for(int i = 0; i != KETTLE_STRING_LENGTH; i++)
	{
		label->contents[i] = ' ';
	}
}

bool checkKettleStringEquality(KettleString a, KettleString b)
{
	for(int i = 0; i != KETTLE_STRING_LENGTH; i++)
	{
		if(a.contents[i] != b.contents[i])
		{
			return false;
		}
	}
	return true;
}

KettleString newKettleString(const char contents[KETTLE_STRING_LENGTH])
{
	KettleString ret;
	clearKettleString(&ret);
	for (int i = 0; i != KETTLE_STRING_LENGTH; i++)
	{
		ret.contents[i] = contents[i];
	}
	return ret;
}

void copyKettleString(KettleString* dest, KettleString* source)
{
	for(int i = 0; i != KETTLE_STRING_LENGTH; i++)
	{
		dest->contents[i] = source->contents[i];
	}
}

//note, this doesn't return size length but instead how many letters there are in the string.
int getKettleStringLength(KettleString* k_string)
{
	int i;
	for(i = 0; k_string->contents[i] != '\0' || i == KETTLE_STRING_LENGTH; i++)
	{
	}
	return i;
}

int findLongestStringInArrayOfKStrings(KettleString* k_string_arr, int amount_of_strings)
{
	int ret = 0;
	for(int i = 0; i != amount_of_strings; i++)
	{
		int curr_str_len = getKettleStringLength(&k_string_arr[i]);
		if(ret < curr_str_len)
		{
			ret = curr_str_len;
		}
	}
	return ret;
}

void stripKettleStringDown(char* buffer_to_write_to, KettleString k_string)
{
}

KettleString generateRandomFileName(char* extension)
{
	KettleString ret;
	sprintf(ret.contents, "%x-%x-%x-%x%s",
	GetRandomValue(0, 255),
	GetRandomValue(0, 255),
	GetRandomValue(0, 255),
	GetRandomValue(0, 255),
	extension
	);
	return ret;
}

#endif
