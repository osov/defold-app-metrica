#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)
#pragma once

#include "extension_private.h"
#include <dmsdk/sdk.h>

namespace dmAppMetrica {

// The same events and messages are in ExtensionJNI.java
// If you change enums here, pls nake sure you update the constants there as well

enum MessageId
{
    MSG_TYPE_NONE = 1
};

enum MessageEvent
{
	EVENT_ONE = 1,
	EVENT_NOT_SUPPORTED = 100,
	EVENT_JSON_ERROR = 101,
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

}

#endif
