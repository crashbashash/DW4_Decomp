extern char igBlendEquationExt_Register[];
extern char thunk_igPsx2BlendEquationExt_GetMetaObject[];
extern char igPsx2BlendEquationExt_GetVTable[];
extern char igBlendEquationExt_GetPublishedMetaObject[];
extern char g_igPsx2BlendEquationExt_callbackList[];
extern char igPsx2BlendEquationExt_className[];
extern char g_igPsx2BlendEquationExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2BlendEquationExt_InitFields();

void igPsx2BlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2BlendEquationExt_metaObject,
        igBlendEquationExt_Register,
        igBlendEquationExt_GetPublishedMetaObject,
        thunk_igPsx2BlendEquationExt_GetMetaObject,
        igPsx2BlendEquationExt_className,
        0x30, /* instance size */
        igPsx2BlendEquationExt_GetVTable,
        &igPsx2BlendEquationExt_InitFields,
        0, /* extra callback item */
        g_igPsx2BlendEquationExt_callbackList /* callback list */
    );
}
