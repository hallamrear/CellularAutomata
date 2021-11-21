#pragma once
#include "Entity.h"
#include "PhysicsProperties.h"

struct CollisionManifold;

class Rigidbody : public Entity
{
private:

protected:
	bool					mGravityEnabled;
	bool					mDragEnabled;
	float					mMass; //Weight of Entity (kg)
	float					mInverseMass;
	float					mDragCoefficient;
	float					mSpeedCap; //Speed cap (u/s)
	float					mRestitution;
	Vector2f				mVelocity;
	Vector2f				mAcceleration;
	Vector2f				mNetForce;
	Vector2f				mExternalForce;
	Collider*				mCollider;
	bool					mIsStatic;

	//Recalculates the inverse mass based on the current mass
	void					CalculateInverseMass();
	void					AddForce(Vector2f force);
	void					AddForce(float X = 0.0f, float Y = 0.0f);

public:
	Rigidbody(
		std::string texture_path, 
		Transform transform,
		PhysicsProperties properties);

					~Rigidbody();

	//Do not call this outside of physics world.
	virtual void	 PhysicsUpdate(double deltaTime);

	virtual void	 Update(double deltaTime) = 0;
	virtual void	 Render() = 0;
	virtual void	 OnCollision(const CollisionManifold& manifold, Rigidbody& other);
	virtual void	 OnOverlap(const CollisionManifold& manifold, Rigidbody& other);

	Vector2f   const GetVelocity()		 const { return mVelocity; }
	Vector2f   const GetAcceleration()	 const { return mAcceleration; }
	bool	   const GetGravityEnabled() const { return mGravityEnabled; }
	bool	   const GetDragEnabled()	 const { return mDragEnabled; }
	float	   const GetMass()			 const { return mMass; };
	float	   const GetInverseMass()	 const { return mInverseMass; };
	float	   const GetRestitution()	 const { return mRestitution; };
	bool	   const GetIsStatic()		 const { return mIsStatic; };
	Collider*  const GetCollider()		 const { return mCollider; };
	//Setters
	virtual void	SetGravityEnabled(const bool state) { mGravityEnabled = state; }
	virtual void	SetDragEnabled(const bool state) { mDragEnabled = state; }
	//Adjusters
	virtual void	AddVelocity(const Vector2f velocity) { mVelocity += velocity; };
	virtual void	AddExternalForce(const Vector2f force) { mExternalForce += force; };
};

