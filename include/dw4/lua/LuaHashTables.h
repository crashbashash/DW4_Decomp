#ifndef DW4_LUAHASHTABLES_H
#define DW4_LUAHASHTABLES_H
#include "dw4/lua/lua.h"

struct LuaProperty;
struct LuaPropertyLink;

extern "C" {

extern unsigned int g_luaFieldBucketShift;
extern unsigned int g_luaFieldBucketCount;
extern unsigned int g_luaFieldCount;
extern LuaHashLink **g_luaFieldBuckets;
extern int g_luaFieldTableBusy;
extern unsigned int g_luaFunctionBucketShift;
extern unsigned int g_luaFunctionBucketCount;
extern unsigned int g_luaFunctionCount;
extern LuaHashLink **g_luaFunctionBuckets;
extern int g_luaFunctionTableBusy;
extern unsigned int g_luaClassBucketShift;
extern unsigned int g_luaClassBucketCount;
extern unsigned int g_luaClassCount;
extern LuaHashLink **g_luaClassBuckets;
extern int g_luaClassTableBusy;
extern unsigned int g_luaPropertyBucketShift;
extern unsigned int g_luaPropertyBucketCount;
extern unsigned int g_luaPropertyCount;
extern LuaProperty **g_luaPropertyBuckets;
extern int g_luaPropertyTableBusy;
extern unsigned int g_luaConstantBucketShift;
extern unsigned int g_luaConstantBucketCount;
extern unsigned int g_luaConstantCount;
extern LuaHashLink **g_luaConstantBuckets;
extern int g_luaConstantTableBusy;
extern unsigned int g_luaEnumBucketShift;
extern unsigned int g_luaEnumBucketCount;
extern unsigned int g_luaEnumCount;
extern LuaHashLink **g_luaEnumBuckets;
extern int g_luaEnumTableBusy;
void LuaPropertyTable_Remove(LuaPropertyLink *link);
void LuaConstantTable_Remove(LuaHashLink *link);
void LuaEnumTable_Remove(LuaHashLink *link);
void LuaFieldTable_Insert(LuaHashLink *link);
void LuaFieldTable_Remove(LuaHashLink *link);
void LuaFieldTable_Resize(void);
void LuaClassTable_Insert(LuaHashLink *link);
void LuaClassTable_Resize(void);
void LuaFunctionTable_Insert(LuaHashLink *link);
void LuaFunctionTable_Remove(LuaHashLink *link);
void LuaFunctionTable_Resize(void);
void LuaPropertyTable_Resize(void);
void LuaConstantTable_Resize(void);
void LuaEnumTable_Resize(void);
void LuaFieldTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaFunctionTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaClassTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaPropertyTable_Link(LuaPropertyLink *link, LuaProperty **buckets, unsigned int bucketCount, unsigned int shift);
void LuaConstantTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaEnumTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);

}

#endif
