extern char igObject_GetMetaObject_ParentAccessor[];
extern char igVectorMorphing_GetVTable[];
extern char thunk_igVectorMorphing_GetMetaObject_00186ec0[];
void FUN_00186ed0(void);
extern char igObject_Register[];
extern char igVectorMorphing_className[];
extern char g_igVectorMorphing_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVectorMorphing_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVectorMorphing_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVectorMorphing_GetMetaObject_00186ec0,
        igVectorMorphing_className,
        8, /* instance size */
        igVectorMorphing_GetVTable,
        0,
        FUN_00186ed0,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}
