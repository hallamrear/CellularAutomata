#pragma once


struct PhysicsProperties
{
	//IsStatic Overrides gravity enabled
	bool  IsStatic = false;
	bool  GravityEnabled = true;
	bool  DragEnabled = true;
	float Mass = 100.0f; //Weight of Entity (kg)
	float DragCoefficient = 0.47f; //Drag coefficient (default to sphere's value of 0.47)
	float SpeedCap = 1000.0f; //Speed cap (u/s)
	float Restitution = 0.5f;

	PhysicsProperties(
		float mass = 100.0f,
		float restitution = 0.5f,
		float speedCap = 1000.0f,
		float dragCoefficient = 0.47f,
		bool dragEnabled = true,
		bool gravityEnabled = true,
		bool isStatic = false)
		: Mass(mass), Restitution(restitution), SpeedCap(speedCap),
		DragCoefficient(dragCoefficient), DragEnabled(dragEnabled),
		GravityEnabled(gravityEnabled), IsStatic(isStatic)
		{
			
		};

	~PhysicsProperties()
	{

	};

};

