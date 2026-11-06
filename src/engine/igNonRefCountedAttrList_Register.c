extern char igNonRefCountedAttrList_GetVTable[];
extern char thunk_igNonRefCountedAttrList_GetMetaObject[];
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedAttrList_callbackList[];
extern char igNonRefCountedAttrList_className[];
extern char g_igNonRefCountedAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedAttrList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedAttrList_GetMetaObject,
        igNonRefCountedAttrList_className,
        0x14, /* instance size */
        igNonRefCountedAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrList_callbackList /* callback list */
    );
}
