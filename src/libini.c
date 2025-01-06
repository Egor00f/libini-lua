#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "libini.h"
#include <sys/ksys.h>

static lua_State *L_glob = NULL;

static void lualibini_enumSetcion(const char *f_name, const char *sec_name)
{
    lua_State *L = L_glob;
    L_glob = NULL;

    if (lua_gettop(L) == 2 &&  // make sure exactly one argument is passed
        lua_isfunction(L, -1)) // and that argument (which is on top of the stack) is a function
    {
        lua_pushstring(L, f_name);
        lua_pushstring(L, sec_name);
        lua_pcall(L_glob, 2, 0, 0); // call a function with one argument and no return values
    }
}

static void lualibini_enumKeys(const char *f_name, const char *sec_name, const char *key_name, const char *key_value)
{
    lua_State *L = L_glob;
    L_glob = NULL;

    if (lua_gettop(L_glob) == 2 &&  // make sure exactly one argument is passed
        lua_isfunction(L_glob, -1)) // and that argument (which is on top of the stack) is a function
    {
        lua_pushstring(L_glob, f_name);
        lua_pushstring(L_glob, sec_name);
        lua_pushstring(L_glob, key_name);
        lua_pushstring(L_glob, key_value);
        lua_pcall(L_glob, 2, 0, 0); // call a function with one argument and no return values
    }
}

static int lualibini_enum_sections(lua_State *L)
{
    while (L_glob != NULL)
    {
        _ksys_thread_yield();
    }
    L_glob = L;

    if (LIBINI_enum_sections(
            luaL_checkstring(L, 1),
            lualibini_enumSetcion) == 0)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_enum_keys(lua_State *L)
{
    while (L_glob != NULL)
    {
        _ksys_thread_yield();
    }
    L_glob = L;

    if (LIBINI_enum_keys(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            lualibini_enumKeys) == 0)
    {
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_get_str(lua_State *L)
{
    char *buffer;

    if (LIBINI_get_str(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            buffer,
            luaL_checkinteger(L, 4)) == 0)
    {
        lua_pushstring(L, buffer);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_set_str(lua_State *L)
{
    char *buffer = luaL_checkstring(L, 4);
    if (LIBINI_get_str(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            buffer,
            strlen(buffer)) == 0)
    {
        lua_pushstring(L, buffer);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_get_int(lua_State *L)
{
    lua_pushinteger(
        L,
        LIBINI_get_int(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            luaL_checkinteger(L, 4)));

    return 1;
}

static int lualibini_set_int(lua_State *L)
{
    if (LIBINI_set_int(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            luaL_checkinteger(L, 4)) == 0)
    {
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_get_color(lua_State *L)
{
    lua_pushinteger(
        L,
        LIBINI_get_color(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            luaL_checkinteger(L, 4)));

    return 1;
}

static int lualibini_set_color(lua_State *L)
{
    if (LIBINI_set_color(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            luaL_checkinteger(L, 4)) == 0)
    {
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_get_shortcut(lua_State *L)
{
    uint32_t mod = 0;
    if (LIBINI_get_shortcut(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2),
            luaL_checkstring(L, 3),
            0,
            &mod) == 0)
    {
        lua_pushinteger(L, mod);

        /* хз как првильно
        lua_createtable(L, 0, 4);

        lua_pushinteger(L, mod & 0x000F);
        lua_setfield(L, -2, "Shift");

        lua_pushinteger(L, mod & 0x00F0);
        lua_setfield(L, -2, "Ctrl");

        lua_pushinteger(L, mod & 0x0F00);
        lua_setfield(L, -2, "Alt");*/
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

static int lualibini_del_section(lua_State *L)
{
    lua_pushinteger(
        L,
        LIBINI_del_section(
            luaL_checkstring(L, 1),
            luaL_checkstring(L, 2)));

    return 1;
}

static const luaL_Reg libiniLib[] = {
    {"enumSections", lualibini_enum_sections},
    {"enumKeys", lualibini_enum_keys},
    {"GetStr", lualibini_get_str},
    {"SetStr", lualibini_set_str},
    {"GetInt", lualibini_get_int},
    {"SetInt", lualibini_set_int},
    {"GetColor", lualibini_get_color},
    {"SetColor", lualibini_set_color},
    {"GetShortcut", lualibini_get_shortcut},
    {"DeleteSection", lualibini_del_section},
    {NULL, NULL}};

LUALIB_API int luaopen_libini(lua_State *L)
{
    if (kolibri_libini_init() == -1)
        luaL_pushfail(L);

    luaL_newlib(L, libiniLib);

    return 1;
}
