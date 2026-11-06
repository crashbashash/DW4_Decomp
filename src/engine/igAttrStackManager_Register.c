extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAttrStackManager_GetVTable[];
extern char thunk_igAttrStackManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAttrStackManager_callbackList[];
extern char igAttrStackManager_className[];
extern char g_igAttrStackManager_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
void FUN_001a58e0(void);
int igAttrStackManager_InitFields();

void igAttrStackManager_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrStackManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrStackManager_GetMetaObject,
        igAttrStackManager_className,
        0x4C, /* instance size */
        igAttrStackManager_GetVTable,
        &igAttrStackManager_InitFields,
        FUN_001a58e0,                         /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrStackManager_callbackList  /* 0-terminated dependency-callback list */
    );
}
