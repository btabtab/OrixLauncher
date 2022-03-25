#ifndef KETTLE_STRING
#define KETTLE_STRING

#define KETTLE_STRING_LENGTH 50

typedef struct KettleString
{
	char contents[KETTLE_STRING_LENGTH];
}
KettleString;

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
#endif
