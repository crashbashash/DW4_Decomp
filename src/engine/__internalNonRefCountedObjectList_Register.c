/* 0x002c2bc0 __internalNonRefCountedObjectList_Register: registers class __internalNonRefCountedObjectList with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char __internalNonRefCountedObjectList_GetVTable[];
extern char thunk___internalNonRefCountedObjectList_GetMetaObject[];
extern char igObject_Register[];
extern char s___internalNonRefCountedObjectList_className_004f6fb0[];
extern char g___internalNonRefCountedObjectList_metaObject_005860e0[];
int igMetaObject_RegisterClass();
int __internalNonRefCountedObjectList_InitFields();

void __internalNonRefCountedObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g___internalNonRefCountedObjectList_metaObject_005860e0, /* published MetaObject slot */
        igObject_Register,                                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,                   /* base class MetaObject accessor */
        thunk___internalNonRefCountedObjectList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s___internalNonRefCountedObjectList_className_004f6fb0,  /* class name */
        0x10,                                                    /* instance size */
        __internalNonRefCountedObjectList_GetVTable,             /* vtable getter */
        &__internalNonRefCountedObjectList_InitFields,           /* field adder */
        0,                                                       /* extra callback item */
        0                                                        /* callback list */
    );
}
