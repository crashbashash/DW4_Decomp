extern char igNonRefCountedObjectStack_GetPublishedMetaObject[];
extern char igAttrStack_GetVTable[];
extern char thunk_igAttrStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igAttrStack_callbackList[];
extern char igAttrStack_className[];
extern char g_igAttrStack_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAttrStack_InitFields();

void igAttrStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrStack_metaObject,
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igAttrStack_GetMetaObject,
        igAttrStack_className,
        0x34, /* instance size */
        igAttrStack_GetVTable,
        &igAttrStack_InitFields,
        0, /* extra callback item */
        g_igAttrStack_callbackList /* callback list */
    );
}
