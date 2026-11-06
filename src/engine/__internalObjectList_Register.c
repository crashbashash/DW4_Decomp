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
        0, /* abstract */
        g___internalObjectList_metaObject,
        __internalNonRefCountedObjectList_Register,
        __internalNonRefCountedObjectList_GetPublishedMetaObject_002c28f0,
        thunk___internalObjectList_GetMetaObject,
        __internalObjectList_className,
        0x10, /* instance size */
        __internalObjectList_GetVTable,
        &__internalObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
