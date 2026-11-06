extern char igAttrSet_GetPublishedMetaObject[];
extern char igOverrideAttrSet_GetVTable[];
extern char thunk_igOverrideAttrSet_GetMetaObject[];
extern char igAttrSet_Register[];
extern char igOverrideAttrSet_className[];
extern char g_igOverrideAttrSet_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igOverrideAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOverrideAttrSet_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igOverrideAttrSet_GetMetaObject,
        igOverrideAttrSet_className,
        0x28, /* instance size */
        igOverrideAttrSet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
