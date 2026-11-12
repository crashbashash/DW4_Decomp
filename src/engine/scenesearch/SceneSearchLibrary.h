#ifndef DW4_SCENE_SEARCH_LIBRARY_H
#define DW4_SCENE_SEARCH_LIBRARY_H

#include "dw4/reflected.h"

/* Library front: the register list, its one registrar and the registration latch. */
extern "C" void thunk_FUN_00238ed0(void);
extern "C" void FUN_00238ed0(void);
extern "C" unsigned char g_SceneSearchLibrary_registered;
extern "C" void SceneSearchLibrary_MarkRegistered(void);
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" int igMetaObject_RegisterClass(...);

/* The igSearchSceneGraph enum field's metaenum (3 values), created on first use. */
extern "C" int DAT_0056dc58[4];
extern "C" int igMetaEnum_Create(...);
extern "C" int DAT_004e9d20[4];
extern "C" int DAT_00498270[4];
extern "C" int DAT_00498280[4];
extern "C" int FUN_00238d70(void);

/* igSearchSceneGraph: an igNamedObject, 0x1C bytes. */
extern "C" igMetaObject *g_igSearchSceneGraph_metaObject[4];
extern "C" igMetaObject *igSearchSceneGraph_GetMetaObject(void);
extern "C" int igSearchSceneGraph_GetVTable(void);
extern "C" void igSearchSceneGraph_Register(void);
extern "C" void thunk_igSearchSceneGraph_GetMetaObject(void);
extern "C" void igSearchSceneGraph_InitFields(void);
extern "C" igMetaObject *Gap__igSearchSceneGraph__vfunc_22(void);
extern "C" char igNamedObject_Register[];
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" char igSearchSceneGraph_className[];
extern "C" char g_igSearchSceneGraph_callbackList[];

/* GetVTable's stack instance and its member destructors. */
struct SearchSceneGraphFrame { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int igObject_InitHeader(...);
extern "C" int FUN_0019c840(...);
extern "C" int FUN_002293d0(...);
extern "C" int FUN_00131bc0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int DAT_0052d0d0[4];
extern "C" void *DAT_00586dc8[4];

/* InitFields' field tables and field helpers. */
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int FUN_002274a0(void);
extern "C" int FUN_002be610(void);
extern "C" int FUN_002dc7a0(...);
extern "C" int DAT_004982a0[4];
extern "C" int DAT_004982b0[4];
extern "C" int DAT_004982c0[4];
extern "C" int DAT_004982d0[4];
extern "C" int DAT_004982e0[4];
extern "C" int DAT_004e9da0[4];

/* The searched scene and the two matrix arrays sized from it (FUN_00239070). */
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int Memory_FreeBuffer(...);
extern "C" int igMetaField_AllocateArray(...);
extern "C" int igObject_Destroy(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int DAT_00562498[4];
extern "C" int DAT_005624a0[4];
extern "C" int FUN_00100610(...);

struct RefCounted { int w0; int refs; int w8; class SceneSource *source; };
class SceneSource {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual int firstMatrixCount();
    virtual int secondMatrixCount();
};
extern "C" void FUN_00239070(int *self, RefCounted *scene);

extern "C" void **FUN_00239200(void **ref, short flags);
extern "C" void **FUN_00239280(void **ref, short flags);
extern "C" void **FUN_00239300(void **ref, short flags);

#endif
