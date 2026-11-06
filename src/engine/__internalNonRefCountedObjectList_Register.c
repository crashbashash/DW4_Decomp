extern char igObject_GetMetaObject_ParentAccessor[];
extern char __internalNonRefCountedObjectList_GetVTable[];
extern char thunk___internalNonRefCountedObjectList_GetMetaObject[];
extern char igObject_Register[];
extern char __internalNonRefCountedObjectList_className[];
extern char g___internalNonRefCountedObjectList_metaObject[];
int igMetaObject_RegisterClass();
int __internalNonRefCountedObjectList_InitFields();

void __internalNonRefCountedObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g___internalNonRefCountedObjectList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk___internalNonRefCountedObjectList_GetMetaObject,
        __internalNonRefCountedObjectList_className,
        0x10, /* instance size */
        __internalNonRefCountedObjectList_GetVTable,
        &__internalNonRefCountedObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
