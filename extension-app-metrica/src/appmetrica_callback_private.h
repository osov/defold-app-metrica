#if defined(DM_PLATFORM_ANDROID)
#pragma once

#include "appmetrica_private.h"
#include <dmsdk/sdk.h>

namespace dmAppMetrica {

// The same events and messages are in AppMetricaJNI.java
// If you change enums here, pls nake sure you update the constants there as well

enum MessageId
{
    MSG_INTERSTITIAL =              1
};

enum MessageEvent
{
    EVENT_CLOSED =                  1
};

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char*json);

} //namespace

#endif
