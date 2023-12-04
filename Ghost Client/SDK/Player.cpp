#include "Player.h"

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