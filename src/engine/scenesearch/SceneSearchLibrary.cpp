#include "src/engine/scenesearch/SceneSearchLibrary.h"

/* SceneSearch's register list: the library has one registrar. */
void thunk_FUN_00238ed0(void) {
    FUN_00238ed0();
}

void SceneSearchLibrary_MarkRegistered(void) {
    if (g_SceneSearchLibrary_registered == 0) {
        g_SceneSearchLibrary_registered = 1;
    }
}

int FUN_00238d70(void) {
    if (DAT_0056dc58[0] == 0) {
        DAT_0056dc58[0] = igMetaEnum_Create(&DAT_004e9d20[0], &DAT_00498270[0], &DAT_00498280[0], 3);
    }
    return DAT_0056dc58[0];
}

igMetaObject *igSearchSceneGraph_GetMetaObject(void) {
    igMetaObject *meta = g_igSearchSceneGraph_metaObject[0];
    if (!meta || ((meta->_validity & 4) != 0) == false)
        FUN_00238ed0();
    return g_igSearchSceneGraph_metaObject[0];
}

/* Builds an instance on the stack and reads its vtable back through the class's vtable offset. */
int igSearchSceneGraph_GetVTable(void) {
    SearchSceneGraphFrame obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = &DAT_0052d0d0[0];
    obj.fC = 0;
    obj.f10 = 0;
    obj.f14 = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem[0] + 916));
    obj.vt = &DAT_0052d0d0[0];
    FUN_0019c840(&obj.f14, -1);
    StringRef_Destruct_00130720(&obj.f10, -1);
    FUN_002293d0(&obj.fC, -1);
    FUN_00131bc0(&obj, 0);
    return vtable;
}

void FUN_00238ed0(void) {
    igMetaObject_RunStaticInit(igSearchSceneGraph_Register);
}

void igSearchSceneGraph_Register(void) {
    SceneSearchLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSearchSceneGraph_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSearchSceneGraph_GetMetaObject,
        igSearchSceneGraph_className,
        0x1C, /* instance size */
        igSearchSceneGraph_GetVTable,
        &igSearchSceneGraph_InitFields,
        0, /* extra callback item */
        g_igSearchSceneGraph_callbackList /* callback list */
    );
}

void thunk_igSearchSceneGraph_GetMetaObject(void) {
    igSearchSceneGraph_GetMetaObject();
}

/* Four fields after igNamedObject's: an object reference, a string, a second reference and an enum. */
void igSearchSceneGraph_InitFields(void) {
    int first;
    void *enumField;
    void *secondRef;
    void *firstRef;
    void *meta;

    meta = (void *)g_igSearchSceneGraph_metaObject[0];
    first = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, &DAT_004982a0[0], 4);
    firstRef = igMetaObject_GetFieldAt(meta, first);
    *(int *)((char *)firstRef + 56) = FUN_002274a0();
    *(unsigned char *)((char *)firstRef + 52) = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, first + 1), &DAT_004e9da0[0]);
    secondRef = igMetaObject_GetFieldAt(meta, first + 2);
    *(int *)((char *)secondRef + 56) = FUN_002be610();
    enumField = igMetaObject_GetFieldAt(meta, first + 3);
    FUN_002dc7a0(enumField, &DAT_004982e0[0]);
    *(int *)((char *)enumField + 52) = (int)&FUN_00238d70;
    igMetaObject_NameFields(meta, &DAT_004982b0[0], &DAT_004982c0[0], &DAT_004982d0[0], first);
}

/* Sets the searched scene (self[8], ref-counted) and reallocates both identity-filled matrix arrays
   (self[9], self[10]) to the counts the scene reports. */
void igActor_SetAnimationSystem(int *self, RefCounted *scene) {
    int firstArray;
    int secondArray;
    int firstCount;
    int secondCount;
    int secondMatrix;
    int j;
    int i;
    int firstMatrix;
    RefCounted *old;

    if (scene != 0) {
        scene->refs = scene->refs + 1;
    }
    old = (RefCounted *)self[8];
    if (old != 0) {
        old->refs = old->refs - 1;
        if ((old->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    self[8] = (int)scene;
    firstCount = ((RefCounted *)self[8])->source->firstMatrixCount();
    secondCount = ((RefCounted *)self[8])->source->secondMatrixCount();
    if (self[9] != 0) {
        Memory_FreeBuffer(self[9]);
        self[9] = 0;
    }
    if (self[10] != 0) {
        Memory_FreeBuffer(self[10]);
        self[10] = 0;
    }
    igMetaField_AllocateArray(&firstArray, DAT_00562498[0], self, firstCount, igObject_GetAllocator(self));
    igMetaField_AllocateArray(&secondArray, DAT_005624a0[0], self, secondCount, igObject_GetAllocator(self));
    firstMatrix = self[9];
    i = 0;
    while (i < firstCount) {
        igMatrix44f_SetIdentity(firstMatrix);
        firstMatrix += 0x40;
        i += 1;
    }
    secondMatrix = self[10];
    j = 0;
    while (j < secondCount) {
        igMatrix44f_SetIdentity(secondMatrix);
        secondMatrix += 0x40;
        j += 1;
    }
}

/* Three smart-pointer destructors: release the held object, then free the pointer when flags > 0. */
void **FUN_00239200(void **ref, short flags) {
    RefCounted *held;

    if (ref != 0) {
        held = (RefCounted *)*ref;
        if (held != 0) {
            held->refs = held->refs - 1;
            if ((held->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
        }
        if (flags > 0) {
            FUN_00100610(ref);
        }
    }
    return ref;
}

void **FUN_00239280(void **ref, short flags) {
    RefCounted *held;

    if (ref != 0) {
        held = (RefCounted *)*ref;
        if (held != 0) {
            held->refs = held->refs - 1;
            if ((held->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
        }
        if (flags > 0) {
            FUN_00100610(ref);
        }
    }
    return ref;
}

void **FUN_00239300(void **ref, short flags) {
    RefCounted *held;

    if (ref != 0) {
        held = (RefCounted *)*ref;
        if (held != 0) {
            held->refs = held->refs - 1;
            if ((held->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
        }
        if (flags > 0) {
            FUN_00100610(ref);
        }
    }
    return ref;
}

igMetaObject *Gap__igSearchSceneGraph__vfunc_22(void) {
    return g_igSearchSceneGraph_metaObject[0];
}
