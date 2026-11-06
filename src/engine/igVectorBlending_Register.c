extern char igObject_GetMetaObject_ParentAccessor[];
extern char igVectorBlending_GetVTable[];
extern char thunk_igVectorBlending_GetMetaObject_00186ff0[];
void FUN_00187000(void);
extern char igObject_Register[];
extern char igVectorBlending_className[];
extern char g_igVectorBlending_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVectorBlending_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVectorBlending_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVectorBlending_GetMetaObject_00186ff0,
        igVectorBlending_className,
        8, /* instance size */
        igVectorBlending_GetVTable,
        0,
        FUN_00187000,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}
