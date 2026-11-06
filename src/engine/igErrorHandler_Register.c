extern char igObject_GetMetaObject_ParentAccessor[];
extern char igErrorHandler_GetVTable[];
extern char thunk_igErrorHandler_GetMetaObject[];
extern char thunk_thunk_FUN_002dca20[];
extern char igObject_Register[];
extern char igErrorHandler_className[];
extern char g_igErrorHandler_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c5f80(void);
void igErrorHandler_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igErrorHandler_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igErrorHandler_GetMetaObject,
        igErrorHandler_className,
        8, /* instance size */
        igErrorHandler_GetVTable,
        FUN_002c5f80,
        thunk_thunk_FUN_002dca20,              /* static-initializer callback item (appended on fresh configuration) */
        0                                      /* 0-terminated dependency-callback list */
    );
}
