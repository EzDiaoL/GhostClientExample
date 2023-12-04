#pragma once
#include "../Java.h"

class CPlayer
{
public:

	CPlayer(jobject instance);
	jclass GetClass();
	void Cleanup();
	bool isSneaking();
	float getHealth();
	int getHunger();
	jobject getInventory();
	void addHealth(float amount);
	void addHunger(int amount);


private:
	jobject playerInstance;
};