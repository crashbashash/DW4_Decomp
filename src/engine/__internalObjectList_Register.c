/* 0x002c2870 __internalObjectList_Register: registers class __internalObjectList with the object system, derived from __internalNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char __internalObjectList_GetVTable[];
extern char thunk___internalObjectList_GetMetaObject[];
extern char __internalNonRefCountedObjectList_GetPublishedMetaObject_002c28f0[];
extern char __internalNonRefCountedObjectList_Register[];
extern char __internalObjectList_className[];
extern char g___internalObjectList_metaObject[];
int igMetaObject_RegisterClass();
int __internalObjectList_InitFields();

void __internalObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0,                                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g___internalObjectList_metaObject,                        /* published MetaObject slot */
        __internalNonRefCountedObjectList_Register,                        /* base class registrar */
        __internalNonRefCountedObjectList_GetPublishedMetaObject_002c28f0, /* base class MetaObject accessor */
        thunk___internalObjectList_GetMetaObject,                          /* own MetaObject accessor (stored at +0x54) */
        __internalObjectList_className,                         /* class name */
        0x10,                                                              /* instance size */
        __internalObjectList_GetVTable,                                    /* vtable getter */
        &__internalObjectList_InitFields,                                  /* field adder */
        0,                                                                 /* extra callback item */
        0                                                                  /* callback list */
    );
}
