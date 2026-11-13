/* lua.h - the Lua binding's public surface: what game code uses to expose classes to scripts.
 *
 * Stock Lua 4.0.1's API and the Alchemy binding's types (bound values, functions and classes),
 * plus the few binding entry points a game class calls. The binding library's own internals
 * (its hash tables, igLuaState, the thread-local slots) stay in src/engine/lua/LuaLibrary.h. */
#ifndef DW4_LUA_H
#define DW4_LUA_H

#include "dw4/reflected.h"

/* Stock Lua 4.0.1's API (lua.h, lualib.h), compiled as C++ like the rest of Lua. */
struct lua_State;
class igMemoryPoolView;
typedef int (*lua_CFunction)(lua_State *L);
enum { LUA_TUSERDATA, LUA_TNIL, LUA_TNUMBER, LUA_TSTRING, LUA_TTABLE, LUA_TFUNCTION };
enum { LUA_ERRRUN = 1, LUA_ERRFILE, LUA_ERRSYNTAX, LUA_ERRMEM, LUA_ERRERR };
lua_State *lua_open(int stacksize, igMemoryPoolView *pool);
void lua_close(lua_State *L);
int lua_gettop(lua_State *L);
void lua_settop(lua_State *L, int index);
void lua_pushvalue(lua_State *L, int index);
void lua_remove(lua_State *L, int index);
void lua_insert(lua_State *L, int index);
int lua_type(lua_State *L, int index);
int lua_tag(lua_State *L, int index);
double lua_tonumber(lua_State *L, int index);
const char *lua_tostring(lua_State *L, int index);
lua_CFunction lua_tocfunction(lua_State *L, int index);
void *lua_touserdata(lua_State *L, int index);
void lua_pushnil(lua_State *L);
void lua_pushnumber(lua_State *L, double n);
void lua_pushstring(lua_State *L, const char *s);
void lua_pushcclosure(lua_State *L, lua_CFunction fn, int n);
void lua_pushusertag(lua_State *L, void *u, int tag);
void lua_gettable(lua_State *L, int index);
void lua_rawget(lua_State *L, int index);
void lua_rawgeti(lua_State *L, int index, int n);
void lua_getglobals(lua_State *L);
int lua_getref(lua_State *L, int ref);
void lua_newtable(lua_State *L);
void lua_settable(lua_State *L, int index);
void lua_rawset(lua_State *L, int index);
void lua_rawseti(lua_State *L, int index, int n);
void lua_settagmethod(lua_State *L, int tag, const char *event);
int lua_ref(lua_State *L, int lock);
int lua_dofile(lua_State *L, const char *filename);
int lua_dostring(lua_State *L, const char *str);
int lua_dobuffer(lua_State *L, const char *buffer, unsigned int size, const char *name);
int lua_newtag(lua_State *L);
void lua_settag(lua_State *L, int tag);
int lua_next(lua_State *L, int index);
int lua_getn(lua_State *L, int index);
void lua_baselibopen(lua_State *L);
void lua_strlibopen(lua_State *L);
void lua_mathlibopen(lua_State *L);

/* The binding's hash tables chain their entries through this header: the key, then the
 * bucket chain's next and previous entries. */
struct LuaHashLink {
    unsigned int key;
    LuaHashLink *next;
    LuaHashLink *prev;
};

/* What a bound value is in C++, `LuaType::kind`. */
enum LuaKind {
    LUA_KIND_NONE,
    LUA_KIND_CHAR,
    LUA_KIND_UCHAR,
    LUA_KIND_SHORT,
    LUA_KIND_USHORT,
    LUA_KIND_INT,
    LUA_KIND_UINT,
    LUA_KIND_LONG,
    LUA_KIND_ULONG,
    LUA_KIND_BOOL,
    LUA_KIND_ENUM,
    LUA_KIND_FLOAT,
    LUA_KIND_DOUBLE,
    LUA_KIND_STRING,
    LUA_KIND_OBJECT,
    LUA_KIND_VOID,
    LUA_KIND_STATIC,
    LUA_KIND_CHARS
};

/* An entry of the binding's hash table for T, chained through its link; N is the table's smallest
 * bucket shift. An entry joins its table as it is built. */
template <class T, int N>
struct Hashed {
    LuaHashLink link;

    Hashed(unsigned int key);
};

namespace Gap {
namespace Core {
/* igObject's virtual functions, for the classes whose vtables the binding builds; the reflected
 * `igObject` is the same object seen as data. Its constructor is igObject_InitHeader. Slot 7 runs
 * once an object is built and slot 8 before it goes. */
class igObject {
public:
    igObject();
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06();
    virtual void userConstruct();
    virtual void userDestruct();
    virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12();
    virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16();
    virtual void vfunc_17(); virtual void vfunc_18();
    virtual int cloneViaMetadata(int copyMode);
    virtual igMetaObject *getMeta();
    unsigned int _refCount;
};
}
namespace Lua {
/* Alchemy's glue between reflected classes and Lua: built, it builds the binding's classes;
 * going, it releases them. */
class igLuaGlue : public Core::igObject {
public:
    struct Class;

    void userDestruct();
    void userConstruct();
    igMetaObject *getMeta();
};
}
}
/* Alchemy's classes are spelled without their namespaces, as everywhere else in the source. */
using Gap::Lua::igLuaGlue;

/* A bound value's type: the C++ kind, how many pointers lead to it, and the Lua types a script
 * may pass for it (`1 << LUA_T*`). An object names its meta-object and its Lua class; an enum
 * keeps its name in the meta-object word. */
struct LuaType {
    int kind : 8;
    int indirection : 2;
    unsigned int byValue : 1;
    unsigned int flag3 : 1;
    unsigned int flag4 : 1;
    unsigned int acceptsTable : 1;
    unsigned int isObjectPointer : 1;
    unsigned int writeBack : 1;
    int acceptedTypes : 16;
    igMetaObject *metaObject;
    igLuaGlue::Class *luaClass;

    LuaType() {}
    LuaType(int kind, int indirection, int flags, const char *className);
    LuaType(const char **names, unsigned int code);
};

/* One argument or result while a bound function runs. */
struct LuaValue {
    LuaType type;
    union {
        signed char c;
        unsigned char uc;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long long ll;
        unsigned long long ull;
        bool b;
        float f;
        double d;
        char *string;
        void *object;
    } data;

    LuaValue() {}
    LuaValue(LuaType *type, lua_State *L, int index);
};

/* A bound C++ function or method, followed by its argument types. Functions of one name and
 * owner chain as overloads. */
struct LuaFunction {
    LuaHashLink link;               /* key: the owner xored with the name's hash */
    const char *name;
    LuaType result;
    igLuaGlue::Class *owner;
    lua_CFunction function;
    LuaFunction *nextOverload;
    short id;
    unsigned short argCount : 12;
    unsigned short hasSelf : 1;
    unsigned short isUnique : 1;
    unsigned short hasOutArgs : 1;
    unsigned short isMethod : 1;

    LuaFunction(lua_CFunction function, int id, const char *name, const LuaType &result, igLuaGlue::Class *owner,
                int isMethod, int argCount);
};

/* A class exposed to Lua: its tags, its class table and the handlers of its tag methods.
 * Instances a script creates carry `instanceTag`, objects it is handed `referenceTag`. It names its
 * base class, which may be built before or after it. Its two virtual functions, which a derived
 * class overrides, bind its functions and constants; the vtable pointer follows the data. The
 * link's key is the name's hash. */
namespace Gap {
namespace Lua {
struct igLuaGlue::Class : Hashed<igLuaGlue::Class, 7> {
    const char *name;
    igMetaObject *metaObject;
    Class *base;
    Class *firstDerived;
    Class *prevSibling;
    Class *nextSibling;
    const char *baseName;
    int instanceTag;
    int referenceTag;
    int classTag;
    int classTableRef;
    LuaFunction *indexGetter;
    LuaFunction *indexSetter;
    lua_CFunction gcHandler;
    lua_CFunction setHandler;
    lua_CFunction getHandler;
    lua_CFunction constructor;
    lua_CFunction peerConstructor;
    Class *alternate;

    Class(const char *name, const char *baseName, lua_CFunction gc, lua_CFunction peerConstructor,
          lua_CFunction get, lua_CFunction set, lua_CFunction construct);
    virtual void registerFunctions() {}
    virtual void registerConstants() {}
};
}
}

/* The pool bound classes are allocated from. */
extern "C" igObject *g_luaGluePool;

extern "C" {
/* Pushes a string as a bound function's result. */
void LuaType_PushString(LuaType *type, lua_State *L, const char *string);
/* Binds a class's functions from the tables a binding generator writes: one code word per
 * function, then its result's and each argument's type code. A method is called through
 * `method`, anything else through `function`; `byId`, if given, receives each method by id. */
void LuaClass_BindFunctions(igLuaGlue::Class *owner, lua_CFunction method, lua_CFunction function,
                            const char **names, int count, const unsigned int *codes, LuaFunction **byId);
/* Formats a binding error and hands it to the registered handler. */
void LuaError(const char *format, ...);
}

#endif
