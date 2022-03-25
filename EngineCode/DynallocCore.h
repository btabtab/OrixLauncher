#ifndef DYNALLOCENGINE
#define DYNALLOCENGINE

#define SUCCESS_CODE 0
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <../MetaLauncher/EngineCode/KettleString.h>

#define OBJECT_SET_LIMIT 30


typedef struct KData
{
	void* data;
	int data_size;
}
KData;

typedef struct KObject
{
	KettleString name;
	KData data;
	bool flag_delete;
}
KObject;

KObject* voidToKobj(void* ptr)
{
	return (KObject*)ptr;
}

/*
This is used to pass functions to the manager to control
rendering / processing for the Kettle Object Types.
*/
typedef void (*KettleObjectWrapperFunction)(KObject*);

typedef struct KettleObjectSet
{
	KettleString name;
	KettleObjectWrapperFunction process;
	KettleObjectWrapperFunction init;
	KettleObjectWrapperFunction deinit;
	KettleObjectWrapperFunction render;
	int size;
}
KettleObjectSet;

KettleObjectSet newKOBJSet(	KettleString name,
							KettleObjectWrapperFunction init,
							KettleObjectWrapperFunction deinit,
							KettleObjectWrapperFunction process,
							KettleObjectWrapperFunction render,
							int size)
{
	KettleObjectSet ret;
	ret.name = name;
	ret.process = process;
	ret.init = init;
	ret.deinit = deinit;
	ret.render = render;
	ret.size = size;
	return ret;
}
#define OBJECT_SET_LIMIT 30
typedef struct DynallocCore
{
	KObject* list;
	int count;

	KettleObjectSet Object_types[OBJECT_SET_LIMIT];
	int type_count;
}
DynallocCore;

DynallocCore** getDynallocCorePtrAddress()
{
	static DynallocCore* core;
	return &core;
}
DynallocCore* getDynallocCore()
{
	return *getDynallocCorePtrAddress();
}
int getDynallocObjCount()
{
	return getDynallocCore()->count;
}
void initDynallocCore()
{
	*(getDynallocCorePtrAddress()) = (DynallocCore*)(malloc(sizeof(DynallocCore)));
	getDynallocCore()->type_count = 0;
	getDynallocCore()->count = 0;
	getDynallocCore()->list = NULL;
}
KObject* getKobj(int index)
{
	return &getDynallocCore()->list[index];
}

void registerNewKObject(KettleObjectSet KOS)
{
	if(getDynallocCore()->type_count <= OBJECT_SET_LIMIT)
	{
		getDynallocCore()->Object_types[getDynallocCore()->type_count++] = KOS;
	}
}

KettleObjectSet* getObjectType(KObject* kobj)
{
	for(int i = 0; i != getDynallocCore()->type_count; i++)
	{
		if(OBJECT_SET_LIMIT <= i)
		{
			// printf("OBJECT_SET_LIMIT <= i");
			exit(0);
		}
		if(checkKettleStringEquality(kobj->name, getDynallocCore()->Object_types[i].name))
		{
			// printf("%s\n", getDynallocCore()->Object_types[i].name.contents);
			return &getDynallocCore()->Object_types[i];
		}
	}
	exit(0);
}


void createKettleData(KObject* kobj)
{
	kobj->data.data = malloc(getObjectType(kobj)->size);
	kobj->data.data_size = getObjectType(kobj)->size;
}

KObject newKObject(KettleString name)
{
	KObject ret;
	ret.name = name;
	createKettleData(&ret);
	ret.flag_delete = false;
	return ret;
}

//implement and test the process, render, init and deinit functions for the KObjs<3.
void runConstructor(KObject* kobj)
{
	getObjectType(kobj)->init(kobj);
}
void runDeconstructor(KObject* kobj)
{
	getObjectType(kobj)->deinit(kobj);
}
void runProcess(KObject* kobj)
{
	getObjectType(kobj)->process(kobj);
}
void runRender(KObject* kobj)
{
	getObjectType(kobj)->render(kobj);
}


void resizeDynallocMemoryUp(KettleString name)
{
	printf("\nresizeDynallocMemoryUp\n");
	getDynallocCore()->list = voidToKobj(realloc(getDynallocCore()->list, sizeof(KObject) * (++getDynallocCore()->count)));

	(*getKobj(getDynallocCore()->count-1)) = newKObject(name);
	
	runConstructor(getKobj(getDynallocCore()->count-1));
}

void createObjectInstance(KettleString name)
{
	for(int i = 0; i != getDynallocCore()->type_count; i++)
	{
		if(checkKettleStringEquality(getDynallocCore()->Object_types[i].name, name))
		{
			resizeDynallocMemoryUp(name);
			return;
		}
	}
	exit(0);
}

void copyKobjList(KObject* destination, int dest_length, KObject* source, int source_length)
{
	for(int i = 0; i != dest_length; i++)
	{
		destination[i] = source[i];
	}
}

void swapKobjs(KObject* a, KObject* b)
{
	KObject swap_buff = *a;
	(*a) = *b;
	(*b) = swap_buff;
}

int getAmountOfDeleteFlaggedObjects()
{
	int j = 0;
	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		if(getKobj(i)->flag_delete)
		{
			j++;
		}
	}
	return j;
}

void organiseKobjsByDeleteTag(KObject* list, int list_length)
{

	for(int j = 0; j != getAmountOfDeleteFlaggedObjects(); j++)
	{
		for(int i = 0; i != list_length-1; i++)
		{
			if(list[i].flag_delete)
			{
				swapKobjs(&list[i], &list[i+1]);
			}
		}
	}
}

void resizeDynallocMemoryDown(int amount)
{
	KObject* old_list = getDynallocCore()->list;
	int old_count = getDynallocCore()->count;

	getDynallocCore()->count = amount;
	getDynallocCore()->list = voidToKobj(calloc(getDynallocCore()->count, sizeof(KObject)));
	copyKobjList(getDynallocCore()->list, getDynallocCore()->count, old_list, old_count);
	if(getDynallocCore()->count == 0)
	{
		getDynallocCore()->list = NULL;
	}

	for(int i = amount; i != old_count; i++)
	{
		free(old_list[i].data.data);
		free(old_list);
	}
}

void cleanUpDynallocCore()
{
	organiseKobjsByDeleteTag(getDynallocCore()->list, getDynallocObjCount());
	resizeDynallocMemoryDown(getDynallocObjCount() - getAmountOfDeleteFlaggedObjects());
}

void processKObjs()
{
	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		// printf("process iteration: %d", i);
		runProcess(getKobj(i));
	}
}
void renderKObjs()
{
	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		// printf("render iteration: %d", i);
		runRender(getKobj(i));
	}
}

#endif
#ifndef DUMMY_CODE
#define DUMMY_CODE
#define DUMMY_OBJECT_NAME newKettleString("DUMMY_OBJECT")

typedef struct DummyStruct
{
	int number;
}
DummyStruct;

void printDummyNum(DummyStruct* dummy)
{
	printf("ID = %d\n", dummy->number);
}

DummyStruct* voidToDmmyptr(void* ptr)
{
	return (DummyStruct*)ptr;
}

void dummyProcess(KObject* kobj)
{
	printf("\ndummy process\n");
	printDummyNum(voidToDmmyptr(kobj->data.data));
}
void dummyInit(KObject* kobj)
{
	static int ID = 0;
	voidToDmmyptr(kobj->data.data)->number = ID++;
	printf("\nInit\n");
	printDummyNum(voidToDmmyptr(kobj->data.data));
}
void dummyDeInit(KObject* kobj)
{
	printf("\ndeInit\n");
	printDummyNum(voidToDmmyptr(kobj->data.data));
}
void dummyRender(KObject* kobj)
{
	printf("\nrender\n");
	printDummyNum(voidToDmmyptr(kobj->data.data));
}
void dummySystem()
{
	system("cls");
	initDynallocCore();
	registerNewKObject(newKOBJSet(
									DUMMY_OBJECT_NAME,
									dummyInit,
									dummyDeInit,
									dummyProcess,
									dummyRender,
									sizeof(DummyStruct)
									)
	);

	int objects_to_generate = 500;
	for(int i = 0; i != objects_to_generate; i++)
	{
		printf("iteration: %d", i);
		resizeDynallocMemoryUp(DUMMY_OBJECT_NAME);
		printf("-- processing-- \n");
		processKObjs();
		printf("-- rendering-- \n");
		renderKObjs();
	}
	int random_numbers = rand() % objects_to_generate + 0;
	for(int i = 0; i != random_numbers; i++)
	{
		getKobj(rand() % objects_to_generate + 0)->flag_delete = true;
		getKobj(rand() % objects_to_generate + 0)->flag_delete = true;
	}

	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		printf("value kobj(%d).flag_delete : %d, ID : %d\n", i, getKobj(i)->flag_delete, ((DummyStruct*)(getKobj(i)->data.data))->number);
	}
	printf("--=--=--=--=--=--=--\n");
	organiseKobjsByDeleteTag(getDynallocCore()->list, getDynallocCore()->count);
	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		printf("value kobj(%d).flag_delete : %d, ID : %d\n", i, getKobj(i)->flag_delete, ((DummyStruct*)(getKobj(i)->data.data))->number);
	}
	printf("Post Delete --=--=--=--=--=--=--\n");
	cleanUpDynallocCore();
	for(int i = 0; i != getDynallocCore()->count; i++)
	{
		printf("value kobj(%d).flag_delete : %d, ID : %d\n", i, getKobj(i)->flag_delete, ((DummyStruct*)(getKobj(i)->data.data))->number);
	}

	// resizeDynallocMemoryDown();
}
/*
This will run the functions that Dynalloc needs
to run every single cycle.
*/
void processDynalloc()
{
	processKObjs();
	cleanUpDynallocCore();
}
#endif