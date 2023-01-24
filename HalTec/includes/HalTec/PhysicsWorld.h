#pragma once
#include "Collision.h"

#define FIXED_TIME_STEP (1.0 / 60.0)
#define IMPULSE_ITERATION_COUNT 8

class Rigidbody;

class PhysicsWorld
{
	static PhysicsWorld* mInstance;
	double mFixedTimestep;
	std::vector<Rigidbody*> mRigidbodies;
	std::vector<CollisionManifold> mManifolds;

	PhysicsWorld(double fixedTimeStep);
	~PhysicsWorld();
	
	void FixedUpdate();
	void Update_Impl(double deltaTime);
	void RegisterRigidbody_Impl(Rigidbody* rb);
	void DeregisterRigidbody_Impl(Rigidbody* rb);

protected:
	static PhysicsWorld* Get();

public:
	
	static void Update(double deltaTime);
	static void RegisterRigidbody(Rigidbody* rb);
	static void DeregisterRigidbody(Rigidbody* rb);
};

