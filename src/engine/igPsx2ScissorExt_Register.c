extern char igScissorExt_Register[];
extern char thunk_igPsx2ScissorExt_GetMetaObject[];
extern char igPsx2ScissorExt_GetVTable[];
extern char igScissorExt_GetPublishedMetaObject[];
extern char g_igPsx2ScissorExt_callbackList[];
extern char igPsx2ScissorExt_className[];
extern char g_igPsx2ScissorExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2ScissorExt_InitFields();

void igPsx2ScissorExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ScissorExt_metaObject,
        igScissorExt_Register,
        igScissorExt_GetPublishedMetaObject,
        thunk_igPsx2ScissorExt_GetMetaObject,
        igPsx2ScissorExt_className,
        0x2C, /* instance size */
        igPsx2ScissorExt_GetVTable,
        &igPsx2ScissorExt_InitFields,
        0, /* extra callback item */
        g_igPsx2ScissorExt_callbackList /* callback list */
    );
}
