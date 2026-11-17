#ifndef DW4_IGLUASTATE_H
#define DW4_IGLUASTATE_H
#include "dw4/lua.h"
#include "dw4/LuaBinding.h"

struct CallbackArray;
class LuaSemaphoreView;
namespace Gap { namespace Lua { class igLuaState; } }

extern "C" {

extern igMetaObject *g_igLuaState_metaObject;
igMetaObject *igLuaState_GetMetaObject(void);
int igLuaState_GetVTable(void);
void igLuaState_EnsureRegistered(void);
CallbackArray *igLuaState_Register(void);
void thunk_igLuaState_GetMetaObject(void);
void igLuaState_InitFields(void);
extern LuaErrorHandler g_luaErrorHandler;
extern void *g_luaErrorHandlerData;
extern Gap::Lua::igLuaState *g_currentLuaState;
extern unsigned char g_luaStatePerThread;
extern int g_luaStateSlot;
extern int g_threadLocalNextSlot;
extern LuaSemaphoreView *g_threadLocalSemaphore;
extern const char *g_luaErrorNames[];
void ThreadLocal_Set(int slot, void *value);
void ThreadLocal_SetForThread(void *thread, int slot, void *value);
int ThreadLocal_NewSlot(void *value);
void ThreadLocal_FreeSlot(int slot);
void igLuaState_MakeCurrent(Gap::Lua::igLuaState *state);

}

#endif
