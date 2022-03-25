#ifndef PROPULSION
#define PROPULSION
#include "PhysicsObject.h"

typedef struct JetEngine
{
	PhysicsObject* physobj;
	int throttle;
	Vector3 thrust_direction;
}
JetEngine;

JetEngine newJetEngine(PhysicsObject* physobj, int throttle, Vector3 thrust_dir)
{
	JetEngine ret;
	ret.physobj = physobj;
	return ret;
}

void updateJetEngine(JetEngine* je)
{
	je->physobj.position = addVectors(je->physobj.position, invertVector(je->thrust_direction));
}

void renderJetEngine(JetEngine* je)
{
	renderPhysObjDebug(&je->physobj);
}

#endif