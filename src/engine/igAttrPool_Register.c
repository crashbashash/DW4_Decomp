extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAttrPool_GetVTable[];
extern char thunk_igAttrPool_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAttrPool_callbackList[];
extern char igAttrPool_className[];
extern char g_igAttrPool_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
void FUN_0013aa90(void);
int igAttrPool_InitFields();

void igAttrPool_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch: writes a gp-relative byte flag only if it is clear. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrPool_GetMetaObject,
        igAttrPool_className,
        0x14, /* instance size */
        igAttrPool_GetVTable,
        &igAttrPool_InitFields,
        FUN_0013aa90,                      /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrPool_callbackList     /* 0-terminated dependency-callback list */
    );
}
