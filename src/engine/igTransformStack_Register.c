extern char igNonRefCountedObjectStack_GetPublishedMetaObject[];
extern char igTransformStack_GetVTable[];
extern char thunk_igTransformStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igTransformStack_callbackList[];
extern char igTransformStack_className[];
extern char g_igTransformStack_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTransformStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformStack_metaObject,
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igTransformStack_GetMetaObject,
        igTransformStack_className,
        0x14, /* instance size */
        igTransformStack_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformStack_callbackList /* callback list */
    );
}
