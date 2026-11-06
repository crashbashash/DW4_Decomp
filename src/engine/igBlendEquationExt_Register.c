extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igBlendEquationExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char igBlendEquationExt_className[];
extern char g_igBlendEquationExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igBlendEquationExt_InitFields();

void igBlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igBlendEquationExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igBlendEquationExt_GetMetaObject,
        igBlendEquationExt_className,
        0x18, /* instance size */
        0,
        &igBlendEquationExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
