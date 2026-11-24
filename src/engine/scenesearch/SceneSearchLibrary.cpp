#include "src/engine/scenesearch/SceneSearchLibrary.h"
#include "dw4/maths/igMath.h"

#pragma push
#pragma readonly_strings on

unsigned char g_SceneSearchLibrary_registered;

/* SceneSearch's register list: the library has one registrar. */
void SceneSearchLibrary_RegisterClasses(void) {
    igSearchSceneGraph_EnsureRegistered();
}

void SceneSearchLibrary_MarkRegistered(void) {
    if (g_SceneSearchLibrary_registered == 0) {
        g_SceneSearchLibrary_registered = 1;
    }
}

static const char *g_igSearchSceneGraph_applicationFindTypeNames[] = {
    "IG_APPLICATION_FIND_ALL", "IG_APPLICATION_FIND_OFTYPE", "IG_APPLICATION_FIND_OFEXACTTYPE",
};
static int g_igSearchSceneGraph_applicationFindTypeValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igSearchSceneGraph_applicationFindTypeMetaEnum;
igMetaObject *g_igSearchSceneGraph_metaObject;
igMetaField *g_igSearchSceneGraph_iterateGraphMetaField;
igMetaField *g_igSearchSceneGraph_searchStringMetaField;
igMetaField *g_igSearchSceneGraph_searchMetaMetaField;
igMetaField *g_igSearchSceneGraph_nextOfTypeCodeMetaField;

int FUN_00238d70(void) {
    if (g_igSearchSceneGraph_applicationFindTypeMetaEnum == 0) {
        g_igSearchSceneGraph_applicationFindTypeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_APPLICATION_FIND_TYPE", g_igSearchSceneGraph_applicationFindTypeNames, g_igSearchSceneGraph_applicationFindTypeValues, 3);
    }
    return (int)g_igSearchSceneGraph_applicationFindTypeMetaEnum;
}

igMetaObject *igSearchSceneGraph_GetMetaObject(void) {
    igMetaObject *meta = g_igSearchSceneGraph_metaObject;
    if (!meta || ((meta->_validity & 4) != 0) == false)
        igSearchSceneGraph_EnsureRegistered();
    return g_igSearchSceneGraph_metaObject;
}

/* Builds an instance on the stack and reads its vtable back through the class's vtable offset. */
int igSearchSceneGraph_GetVTable(void) {
    SearchSceneGraphFrame obj;
    int vtable;

    igObject_InitHeader((igObject *)&obj);
    obj.f8 = 0;
    obj.vt = &g_igSearchSceneGraph_vtable[0];
    obj.fC = 0;
    obj.f10 = 0;
    obj.f14 = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igSearchSceneGraph_vtable[0];
    igSmartPointer_igMetaObject_Destruct((igSmartPointer<igObject> *)&obj.f14, -1);
    igStringRef_Destruct((igStringRef *)&obj.f10, -1);
    igSmartPointer_igIterateGraph_Destruct((igSmartPointer<igObject> *)&obj.fC, -1);
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return vtable;
}

void igSearchSceneGraph_EnsureRegistered(void) {
    igMetaObject_RunStaticInit(igSearchSceneGraph_Register);
}

static igMetaObjectCallback g_igSearchSceneGraph_callbackList[] = { igIterateGraph_EnsureRegistered, igMetaObject_EnsureRegistered, 0 };

CallbackArray *igSearchSceneGraph_Register(void) {
    SceneSearchLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSearchSceneGraph_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igSearchSceneGraph_GetMetaObjectFunction,
        "igSearchSceneGraph",
        0x1C, /* instance size */
        igSearchSceneGraph_GetVTable,
        &igSearchSceneGraph_InitFields,
        0, /* extra callback item */
        g_igSearchSceneGraph_callbackList /* callback list */
    );
}

void igSearchSceneGraph_GetMetaObjectFunction(void) {
    igSearchSceneGraph_GetMetaObject();
}

static FieldFactory g_igSearchSceneGraph_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
};
static const char *g_igSearchSceneGraph_fieldTable[] = {
    "_iterateGraph",
    "_searchString",
    "_searchMeta",
    "_nextOfTypeCode",
};
static igMetaField **g_igSearchSceneGraph_fieldHandles[] = {
    &g_igSearchSceneGraph_iterateGraphMetaField,
    &g_igSearchSceneGraph_searchStringMetaField,
    &g_igSearchSceneGraph_searchMetaMetaField,
    &g_igSearchSceneGraph_nextOfTypeCodeMetaField,
};
static int g_igSearchSceneGraph_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

/* Four fields after igNamedObject's: an object reference, a string, a second reference and an enum. */
void igSearchSceneGraph_InitFields(void) {
    int first;
    void *enumField;
    void *secondRef;
    void *firstRef;
    igMetaObject *meta;

    meta = g_igSearchSceneGraph_metaObject;
    first = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igSearchSceneGraph_ctorTable, 4);
    firstRef = igMetaObject_GetFieldAt(meta, first);
    *(int *)((char *)firstRef + 56) = (int)igIterateGraph_GetOrCreateMetaObject();
    *(unsigned char *)((char *)firstRef + 52) = 1;
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, first + 1)))->setDefault("");
    secondRef = igMetaObject_GetFieldAt(meta, first + 2);
    *(int *)((char *)secondRef + 56) = (int)igMetaObject_GetOrCreateMetaObject();
    enumField = igMetaObject_GetFieldAt(meta, first + 3);
    ((Gap::Core::igEnumMetaField *)enumField)->setDefault(0);
    *(int *)((char *)enumField + 52) = (int)&FUN_00238d70;
    igMetaObject_NameFields(meta, g_igSearchSceneGraph_fieldTable, g_igSearchSceneGraph_fieldHandles, g_igSearchSceneGraph_fieldOffsets, first);
}

/* Sets the actor's animation combiner (reference-counted) and reallocates both identity-filled matrix
   caches to the bone and blend-matrix counts of the combiner's hierarchy. */
void igActor_SetAnimationSystem(igActor *self, igAnimationCombiner *combiner) {
    int boneStatus;
    int blendStatus;
    int boneCount;
    int blendCount;
    int blendMatrix;
    int j;
    int i;
    int boneMatrix;
    igAnimationCombiner *old;

    igObject::ref(combiner);
    old = (igAnimationCombiner *)self->_animationSystem;
    igObject::release(old);
    self->_animationSystem = (int)combiner;
    boneCount = ((AnimHierarchyCounts *)((igAnimationCombiner *)self->_animationSystem)->_animHierarchy)->getBoneCount();
    blendCount = ((AnimHierarchyCounts *)((igAnimationCombiner *)self->_animationSystem)->_animHierarchy)->getBlendMatrixCount();
    if (self->_boneMatrixCacheArray != 0) {
        Memory_FreeBuffer((void *)self->_boneMatrixCacheArray);
        self->_boneMatrixCacheArray = 0;
    }
    if (self->_blendMatrixCacheArray != 0) {
        Memory_FreeBuffer((void *)self->_blendMatrixCacheArray);
        self->_blendMatrixCacheArray = 0;
    }
    igMetaField_AllocateArray(&boneStatus, (igMemoryRefMetaField *)Gap::Sg::igActor::k_boneMatrixCacheArray, self, boneCount, ((Gap::Core::igObject *)self)->getMemoryPool());
    igMetaField_AllocateArray(&blendStatus, (igMemoryRefMetaField *)Gap::Sg::igActor::k_blendMatrixCacheArray, self, blendCount, ((Gap::Core::igObject *)self)->getMemoryPool());
    boneMatrix = self->_boneMatrixCacheArray;
    i = 0;
    while (i < boneCount) {
        igMatrix44f_SetIdentity((float *)boneMatrix);
        boneMatrix += 0x40;
        i += 1;
    }
    blendMatrix = self->_blendMatrixCacheArray;
    j = 0;
    while (j < blendCount) {
        igMatrix44f_SetIdentity((float *)blendMatrix);
        blendMatrix += 0x40;
        j += 1;
    }
}

/* Three smart-pointer destructors: release the held object, then free the pointer when flags > 0. */
igSmartPointer<igObject> *igSmartPointer_igLightingStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void **FUN_00239280(void **ref, short flags) {
    RefCounted *held;

    if (ref != 0) {
        held = (RefCounted *)*ref;
        if (held != 0) {
            held->refs = held->refs - 1;
            if ((held->refs & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)held);
            }
        }
        if (flags > 0) {
            operator delete(ref);
        }
    }
    return ref;
}

void **igSmartPointer_igCamera_Destruct(void **ref, short flags) {
    RefCounted *held;

    if (ref != 0) {
        held = (RefCounted *)*ref;
        if (held != 0) {
            held->refs = held->refs - 1;
            if ((held->refs & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)held);
            }
        }
        if (flags > 0) {
            operator delete(ref);
        }
    }
    return ref;
}

igMetaObject *igSearchSceneGraph_GetMeta(void) {
    return g_igSearchSceneGraph_metaObject;
}

/* A sixteen-colour palette: black, grey, the six half-intensity colours, white, silver, the six full ones. */
const igVec4f g_colorPalette[16] = {
    igVec4f(0.0, 0.0, 0.0, 1),
    igVec4f(0.5, 0.5, 0.5, 1),
    igVec4f(0.5, 0.0, 0.0, 1),
    igVec4f(0.5, 0.5, 0.0, 1),
    igVec4f(0.0, 0.5, 0.0, 1),
    igVec4f(0.0, 0.5, 0.5, 1),
    igVec4f(0.0, 0.0, 0.5, 1),
    igVec4f(0.5, 0.0, 0.5, 1),
    igVec4f(1.0, 1.0, 1.0, 1),
    igVec4f(0.75, 0.75, 0.75, 1),
    igVec4f(1.0, 0.0, 0.0, 1),
    igVec4f(1.0, 1.0, 0.0, 1),
    igVec4f(0.0, 1.0, 0.0, 1),
    igVec4f(0.0, 1.0, 1.0, 1),
    igVec4f(0.0, 0.0, 1.0, 1),
    igVec4f(1.0, 0.0, 1.0, 1),
};

#pragma pop
