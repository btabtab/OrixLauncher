
#ifndef NODESYSTEM
#define NODESYSTEM

typedef struct Node
{
	struct Node* next_node;
	struct Node* previous_node;
	void* contents;
}
Node;

/*
Gets the next node.

*/
Node* getNextNode(Node* this)
{
	static int calls = 0;
	calls++;

	if(!this->next_node)
	{
		return this;
	}
	return (Node*)this->next_node;
}

Node* getPrevNode(Node* this)
{
	if(!this->previous_node)
	{
		return NULL;
	}
	return this->previous_node;
}

//returns the address of the newly created node.
Node* createNode(Node* this, void* contents)
{
	//creates a node attached to the current node.
	this->next_node = malloc(sizeof(Node));
	
	if(!this->next_node)
	{
		//TODO: implement error handling properly and make this an error that can be reporte do the system sometime pls<3.
		exit(0);
	}

	//initialises the new node.
	getNextNode(this)->contents = contents;
	getNextNode(this)->previous_node = this;
	getNextNode(this)->next_node = NULL;
	//returns the
	return getNextNode(this);
}
#include <stdio.h>
//Kills the node attached to the current node;
void killNode(Node* this)
{
	free(getNextNode(this));
	this->next_node = NULL;
}

int getNodesInChain(Node* head)
{
	Node* next_node = getNextNode(head);
	int nodes;
	for(nodes = 0; next_node; nodes++)
	{
		next_node = getNextNode(next_node);
	}
	return nodes;
}

Node* getNode(Node* head, int node_to_get)
{
	/*
	if the ndoe it is trying to get is bigger than the nodes
	in the chain then it will return the last available node
	*/
	for(int i = 0; (i != node_to_get) || (!head->next_node); i++)
	{
		head = getNextNode(head);
	}
	return head;
}

Node* getLastNode(Node* head)
{
	Node* last_node = getNextNode(head);
	for(int i = 0; last_node; i++)
	{
		last_node = getNextNode(last_node);
	}
	return last_node;
}

Node* getNodeAtEndOfChain(Node* this)
{
	Node* next = this;
	//if node after "next" is NULL then that means that this is the final part of the chain.
	if(!getNextNode(next))
	{
		return next;
	}
	next = getNodeAtEndOfChain(this);
	return next;
}

Node* addNodeToEndOfChain(Node* head, void* contents)
{
	return createNode(getLastNode(head), contents);
}

void removeLastNodeFromChain(Node* head)
{
	killNode(getLastNode(head));
}

float getRandomDecimal()
{
	return (float)((rand() % 1000 + 0) / 1000);
}

void visualNodeDemo()
{
	Camera camera = initialiseRaylibCameraForDemo(800, 800, "NodeDemo");

	PhysicsObject physobjs[2] =
	{
		newPhysicsObject((Vector3){0, 0, 0}, (Vector3){-.1, -.0, -.1}, 0.005f),
		newPhysicsObject((Vector3){0, 0, 0}, (Vector3){-.1, -.1, -.1}, 0.005f),
	};
	Node head = {0, 0, &physobjs[0]};
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			BeginMode3D(camera);
			{
				if(IsKeyPressed(KEY_R))
				{
					visualNodeDemo();
					return;
				}
				if(IsKeyPressed(KEY_N))
				{
					PhysicsObject* obj = malloc(sizeof(PhysicsObject));
					*obj = newPhysicsObject((Vector3){0, 0, 0}, (Vector3){getRandomDecimal(), getRandomDecimal(), getRandomDecimal()}, 0.5);
					addNodeToEndOfChain(&head, obj);
				}
				if(IsKeyPressed(KEY_D))
				{
					removeLastNodeFromChain(&head);
				}
				renderPhysObjDebug((PhysicsObject*)head.contents);
				updatePhysicsObjectWeight((PhysicsObject*)head.contents);
				updatePhysicsObjectPosition((PhysicsObject*)head.contents);

//////////////////////////////////////////////////////////////////////////////
				// renderPhysObjDebug((PhysicsObject*)getLastNode(&head));
				// updatePhysicsObjectWeight((PhysicsObject*)getLastNode(&head));
				// updatePhysicsObjectPosition((PhysicsObject*)getLastNode(&head));
//////////////////////////////////////////////////////////////////////////////

				// renderPhysObjDebug((PhysicsObject*)getNextNode(&head)->contents);
			}
			EndMode3D();

			char text_buff[30];
			sprintf(text_buff, "<< nodes: %d >>", getNodesInChain(&head));
			DrawText(text_buff, 30, 30, 10, RED);
			DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow();
	// return 0;
}

#endif