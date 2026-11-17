#ifndef DW4_IGLUAGLUE_H
#define DW4_IGLUAGLUE_H
#include "dw4/lua/lua.h"

struct CallbackArray;

extern "C" {

extern igMetaObject *g_igLuaGlue_metaObject;
igMetaObject *igLuaGlue_GetOrCreateMetaObject(void);
igMetaObject *igLuaGlue_GetMetaObject(void);
int igLuaGlue_GetVTable(void);
void igLuaGlue_EnsureRegistered(void);
CallbackArray *igLuaGlue_Register(void);
void thunk_igLuaGlue_GetMetaObject(void);

}

#endif
