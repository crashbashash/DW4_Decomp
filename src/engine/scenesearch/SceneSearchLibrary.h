#ifndef DW4_SCENE_SEARCH_LIBRARY_H
#define DW4_SCENE_SEARCH_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/ClassRegistration.h"
#include "dw4/igObject.h"
#include "dw4/igObjectSystem.h"

typedef void (*igMetaObjectCallback)();
typedef igMetaField *(*FieldFactory)(void *);

/* Library front: the register list, its one registrar and the registration latch. */
extern "C" void igSearchSceneGraph_EnsureRegistered(void);
extern "C" void SceneSearchLibrary_MarkRegistered(void);
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" int igMetaObject_RegisterClass(...);

/* The igSearchSceneGraph enum field's metaenum (3 values), created on first use. */
extern "C" igMetaEnum *igMetaEnum_Create(const char *name, const char **names, int *values, int count);
extern "C" int FUN_00238d70(void);

/* igSearchSceneGraph: an igNamedObject, 0x1C bytes. */
extern "C" igMetaObject *igSearchSceneGraph_GetMetaObject(void);
extern "C" int igSearchSceneGraph_GetVTable(void);
extern "C" void igSearchSceneGraph_Register(void);
extern "C" void thunk_igSearchSceneGraph_GetMetaObject(void);
extern "C" void igSearchSceneGraph_InitFields(void);
extern "C" igMetaObject *Gap__igSearchSceneGraph__vfunc_22(void);
extern "C" char igNamedObject_Register[];
extern "C" char igNamedObject_GetPublishedMetaObject[];

/* GetVTable's stack instance and its member destructors. */
struct SearchSceneGraphFrame { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int igSmartPointer_igMetaObject_Destruct(...);
extern "C" int FUN_002293d0(...);
extern "C" int igNamedObject_Destroy(...);
extern "C" int igStringRef_Destruct(...);
extern "C" int g_igSearchSceneGraph_vtable[4];
/* The object system's byte offset of the vtable word inside an object. */
struct ObjectSystemView { char pad[916]; int vtableProbeOffset; };

/* InitFields' field tables and field helpers. */
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int FUN_002274a0(void);
extern "C" int igMetaObject_GetOrCreateMetaObject(void);
extern "C" int igEnumMetaField_SetDefaultValue(void *field, const int &value);
extern "C" igMetaField *igObjectRefMetaField_Create(void *);
extern "C" igMetaField *igStringMetaField_Create(void *);
extern "C" igMetaField *igEnumMetaField_Create(void *);
extern "C" void FUN_00227620(void);
extern "C" void igMetaObject_EnsureRegistered(void);

/* The searched scene and the two matrix arrays sized from it (igActor_SetAnimationSystem). */
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int Memory_FreeBuffer(...);
extern "C" int igMetaField_AllocateArray(...);
extern "C" int DAT_00562498[4];
extern "C" int DAT_005624a0[4];

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
extern "C" void igActor_SetAnimationSystem(int *self, RefCounted *scene);

extern "C" void **igSmartPointer_igLightingStateAttr_Destruct(void **ref, short flags);
extern "C" void **FUN_00239280(void **ref, short flags);
extern "C" void **FUN_00239300(void **ref, short flags);

#endif
