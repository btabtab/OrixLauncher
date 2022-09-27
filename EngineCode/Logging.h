#ifndef LOGGING
#define LOGGING

#include <stdlib.h>
#include <stdio.h>

#include "KettleString.h"

void logData(KettleString kstr)
{
	char save_buffer[KETTLE_STRING_LENGTH * 3] = "";
	static bool first_run = true;
#ifndef PLATFORM_WEB
	if(first_run)
	{
		system("date /t > log.txt");
		system("time /t >> log.txt");
		first_run = !first_run;
	}
	sprintf(save_buffer, "echo %s >> log.txt",  kstr.contents);
	system(save_buffer);
#else
	printf("LOG: %s", kstr.contents);
#endif
}

#endif