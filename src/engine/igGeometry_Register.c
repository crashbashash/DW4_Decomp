extern char igAttrSet_GetPublishedMetaObject[];
extern char igGeometry_GetVTable[];
extern char thunk_igGeometry_GetMetaObject[];
extern char igAttrSet_Register[];
extern char g_igGeometry_callbackList[];
extern char igGeometry_className[];
extern char g_igGeometry_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
/* Code in the gap after this function. */
extern int igGeometry_InitFields_0019fca0[4];
extern int igGeometry_PostInit_0019fdd0[4];
void igGeometry_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometry_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igGeometry_GetMetaObject,
        igGeometry_className,
        0x2C, /* instance size */
        igGeometry_GetVTable,
        &igGeometry_InitFields_0019fca0[0],
        &igGeometry_PostInit_0019fdd0[0], /* extra callback item */
        g_igGeometry_callbackList /* callback list */
    );
}
