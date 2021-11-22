#pragma once

//todo : release functions for all the singletons

class Time
{
private:
	static Time* mInstance;
	double& mDeltaTime;

	inline Time(double& dt) 
		: mDeltaTime(dt)
	{

	}

	inline ~Time()
	{
		mDeltaTime = 0.0;
	}

public:
	static Time* Get(double& dt)
	{
		if (!mInstance)
			mInstance = new Time(dt);

		return mInstance;
	}

	static void Release()
	{
		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}

	static const double DeltaTime()
	{
		double d;
		return Get(d)->mDeltaTime;
	}
};

