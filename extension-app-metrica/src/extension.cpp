#define EXTENSION_NAME AppMetricaExt
#define LIB_NAME "AppMetrica"
#define MODULE_NAME "appmetrica"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#include "extension_private.h"
#include "extension_callback_private.h"
#include "utils/LuaUtils.h"

namespace dmAppMetrica {

static int Lua_Initialize(lua_State* L)
{
   DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Initialize UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, "%s", msg);
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

static int Lua_ReportEvent(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for ReportEvent 1 variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, "%s", msg);
        return 0;
    }
    if (lua_type(L, 2) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for ReportEvent 2 variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, "%s", msg);
        return 0;
    }
    const char* s1 = luaL_checkstring(L, 1);
    const char* s2 = luaL_checkstring(L, 2);
    ReportEvent(s1, s2);
    return 0;
}

static int Lua_SendRevenue(lua_State *L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for SendRevenue 1 variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, "%s", msg);
        return 0;
    }
    if (lua_type(L, 2) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for SendRevenue 2 variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, "%s", msg);
        return 0;
    }
    if (lua_type(L, 3) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for SendRevenue 3 variable '%s'.", luaL_typename(L, 3), lua_tostring(L, 3));
        luaL_error(L, "%s", msg);
        return 0;
    }
    if (lua_type(L, 4) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for SendRevenue 4 variable '%s'.", luaL_typename(L, 4), lua_tostring(L, 4));
        luaL_error(L, "%s", msg);
        return 0;
    }
    if (lua_type(L, 5) != LUA_TSTRING)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for SendRevenue 5 variable '%s'.", luaL_typename(L, 5), lua_tostring(L, 5));
        luaL_error(L, "%s", msg);
        return 0;
    }
    const char* s1 = luaL_checkstring(L, 1);
    const char* s2 = luaL_checkstring(L, 2);
    const char* s3 = luaL_checkstring(L, 3);
    const char* s4 = luaL_checkstring(L, 4);
    const char* s5 = luaL_checkstring(L, 5);
    SendRevenue(s1, s2, s3, s4, s5);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"set_callback", Lua_SetCallback},
    {"report_event", Lua_ReportEvent},
    {"send_revenue", Lua_SendRevenue},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Module_methods);

    #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(EVENT_ONE)
    SETCONSTANT(EVENT_NOT_SUPPORTED)
    SETCONSTANT(EVENT_JSON_ERROR)

    #undef SETCONSTANT

    lua_pop(L, 1);
}

static dmExtension::Result AppInitializeApp(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeApp(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    Initialize_Ext();
    InitializeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeApp(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeApp(dmExtension::Params* params)
{
    FinalizeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateApp(dmExtension::Params* params)
{
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

static void OnEventApp(dmExtension::Params* params, const dmExtension::Event* event)
 {
    switch(event->m_Event)
    {
        case dmExtension::EVENT_ID_ACTIVATEAPP:
            ActivateApp();
            break;
    }
 }

}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmAppMetrica::AppInitializeApp, dmAppMetrica::AppFinalizeApp, dmAppMetrica::InitializeApp, dmAppMetrica::UpdateApp, dmAppMetrica::OnEventApp, dmAppMetrica::FinalizeApp)

#else

static  dmExtension::Result InitializeApp(dmExtension::Params* params)
{
    dmLogInfo("Registered extension AppMetrica (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeApp(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeApp, 0, 0, FinalizeApp)

#endif // Android
