#include "Minecraft.h"

CPlayer::CPlayer(jobject instance)
{
	this->playerInstance = instance;
}

void CPlayer::Cleanup()
{
	lc->env->DeleteLocalRef(this->playerInstance);
}

jclass CPlayer::GetClass()
{
	return lc->GetClass("net.minecraft.entity.Entity");
}

bool CPlayer::isSneaking()
{
	jmethodID isSneaking = lc->env->GetMethodID(this->GetClass(), "isSneaking", "()Z");

	bool rtrn = lc->env->CallBooleanMethod(this->playerInstance, isSneaking);

	return rtrn;
}

float CPlayer::getHealth()
{
	jmethodID getHealth = lc->env->GetMethodID(this->GetClass(), "getHealth", "()F");
	float rtrn = lc->env->CallFloatMethod(this->playerInstance, getHealth);
	return rtrn;
}

int CPlayer::getHunger()
{
	jmethodID getHunger = lc->env->GetMethodID(this->GetClass(), "getHunger", "()I");
	int rtrn = lc->env->CallIntMethod(this->playerInstance, getHunger);
	return rtrn;
}

jobject CPlayer::getInventory()
{
	jmethodID getInventory = lc->env->GetMethodID(this->GetClass(), "getInventory", "()Lnet/minecraft/inventory/Inventory;");
	jobject rtrn = lc->env->CallObjectMethod(this->playerInstance, getInventory);
	return rtrn;
}

void CPlayer::addHealth(float amount)
{
	jmethodID addHealth = lc->env->GetMethodID(this->GetClass(), "addHealth", "(F)V");
	lc->env->CallVoidMethod(this->playerInstance, addHealth, amount);
}

void CPlayer::addHunger(int amount)
{
	jmethodID addHunger = lc->env->GetMethodID(this->GetClass(), "addHunger", "(I)V");
	lc->env->CallVoidMethod(this->playerInstance, addHunger, amount);
}