#define EXTENSION_NAME AppMetricaExt
#define LIB_NAME "AppMetrica"
#define MODULE_NAME "appmetrica"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "appmetrica_private.h"
#include "appmetrica_callback_private.h"
#include "utils/LuaUtils.h"

namespace dmAppMetrica {

static int Lua_Initialize(lua_State* L)
{
   DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Initialize UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* unitId_lua = luaL_checkstring(L, 1);
    Initialize(unitId_lua);
    return 0; 
}

static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"set_callback", Lua_SetCallback},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Module_methods);

    #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(EVENT_CLOSED)
    SETCONSTANT(EVENT_NOT_SUPPORTED)

    #undef SETCONSTANT

    lua_pop(L, 1);
}

static dmExtension::Result AppInitializeAppMetrica(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeAppMetrica(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    Initialize_Ext();
    InitializeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeAppMetrica(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeAppMetrica(dmExtension::Params* params)
{
    FinalizeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateAppMetrica(dmExtension::Params* params)
{
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

static void OnEventAppMetrica(dmExtension::Params* params, const dmExtension::Event* event)
 {
    switch(event->m_Event)
    {
        case dmExtension::EVENT_ID_ACTIVATEAPP:
            ActivateApp();
            break;
    }
 }

} //namespace dmAppMetrica

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmAppMetrica::AppInitializeAppMetrica, dmAppMetrica::AppFinalizeAppMetrica, dmAppMetrica::InitializeAppMetrica, dmAppMetrica::UpdateAppMetrica, dmAppMetrica::OnEventAppMetrica, dmAppMetrica::FinalizeAppMetrica)

#else

static  dmExtension::Result InitializeAppMetrica(dmExtension::Params* params)
{
    dmLogInfo("Registered extension AppMetrica (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeAppMetrica(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeAppMetrica, 0, 0, FinalizeAppMetrica)

#endif // Android
