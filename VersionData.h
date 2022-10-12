#ifndef METAL_MAIN_VERSION_ID

#include <stdlib.h>
#include <stdio.h>

//Every version with a new feature increments the METAL_MAIN_VERSION_ID number.
#define METAL_MAIN_VERSION_ID 0X0001
/*Every version released for bug fix sakes increments the
METAL_REVISION_ID number (it does however get reset every new version).*/
#define METAL_REVISION_ID 0x0001

void verifyVersion(int version_current_program_is_written_for)
{
	if(version_current_program_is_written_for != METAL_MAIN_VERSION_ID)
	{
		if(METAL_MAIN_VERSION_ID < version_current_program_is_written_for)
		{
			printf("This program was written for an older version of the METAlauncher.");
		}
		if(METAL_MAIN_VERSION_ID > version_current_program_is_written_for)
		{
			printf("This program was written for a newer version of the METAlauncher.");
		}
		exit(METAL_MAIN_VERSION_ID);
	}
	printf("This is running on version: %x\n", METAL_MAIN_VERSION_ID);
}
#endif