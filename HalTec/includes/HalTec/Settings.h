#pragma once
#include "Vector2.h"

class Settings
{
private:
	static Settings* mInstance;

	Settings();
	~Settings();

	int		 mMaxLogMessages;
	bool	 mDrawColliders;
	bool	 mDrawLog;
	Vector2f mWindowCentre;
	Vector2f mWindowDimensions;
	Vector2f mGravityDirection;

public:
	static Settings* Get();

	bool GetDrawLog() const;
	void SetDrawLog(bool state);
	bool GetDrawColliders() const;
	void SetDrawColliders(bool state);
	Vector2f GetWindowCentre() const;
	Vector2f GetWindowDimensions() const;
	Vector2f GetGravityDirection() const;
	void SetGravityDirection(Vector2f direction);
	void SetWindowDimensions(Vector2f dimensions);
	void SetMaxLogMessages(int count);
	int GetMaxLogMessages() const;
};

