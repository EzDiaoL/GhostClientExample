#pragma once
#include "../Java.h"
#include "Player.h"

class CMinecraft
{
public:
    jclass GetClass();
    jobject GetInstance();

    CPlayer* GetLocalPlayer();
};
