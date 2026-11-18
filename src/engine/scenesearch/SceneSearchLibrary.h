#ifndef DW4_SCENE_SEARCH_LIBRARY_H
#define DW4_SCENE_SEARCH_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igMetaObject.h"

typedef void (*igMetaObjectCallback)();
typedef igMetaField *(*FieldFactory)(struct igMemoryPoolView *pool);

/* Library front: the register list, its one registrar and the registration latch. */
extern "C" void igSearchSceneGraph_EnsureRegistered(void);
extern "C" void SceneSearchLibrary_MarkRegistered(void);

/* The igSearchSceneGraph enum field's metaenum (3 values), created on first use. */
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
extern "C" int FUN_00238d70(void);

/* igSearchSceneGraph: an igNamedObject, 0x1C bytes. */
extern "C" igMetaObject *igSearchSceneGraph_GetMetaObject(void);
extern "C" int igSearchSceneGraph_GetVTable(void);
extern "C" CallbackArray *igSearchSceneGraph_Register(void);
extern "C" void igSearchSceneGraph_GetMetaObjectFunction(void);
extern "C" void igSearchSceneGraph_InitFields(void);
extern "C" igMetaObject *igSearchSceneGraph_GetMeta(void);

/* GetVTable's stack instance and its member destructors. */
struct SearchSceneGraphFrame { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMetaField.h"
extern "C" int FUN_002293d0(...);
extern "C" int g_igSearchSceneGraph_vtable[4];
/* InitFields' field tables and field helpers. */
extern "C" int igIterateGraph_GetOrCreateMetaObject(void);
extern "C" void FUN_00227620(void);

struct RefCounted { int w0; int refs; };
/* An animation combiner's hierarchy: slots 22 and 23 count its bones and its blend matrices. */
class AnimHierarchyCounts {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual int getBoneCount();
    virtual int getBlendMatrixCount();
};
#include "dw4/scenegraph/igActor.h"

extern "C" void **FUN_00239280(void **ref, short flags);
extern "C" void **igSmartPointer_igCamera_Destruct(void **ref, short flags);

#endif
