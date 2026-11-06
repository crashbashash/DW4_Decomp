extern char igMultiTextureExt_Register[];
extern char thunk_igPsx2MultiTextureExt_GetMetaObject[];
extern char igPsx2MultiTextureExt_GetVTable[];
extern char igMultiTextureExt_GetPublishedMetaObject[];
extern char g_igPsx2MultiTextureExt_callbackList[];
extern char igPsx2MultiTextureExt_className[];
extern char g_igPsx2MultiTextureExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2MultiTextureExt_InitFields();

void igPsx2MultiTextureExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2MultiTextureExt_metaObject,
        igMultiTextureExt_Register,
        igMultiTextureExt_GetPublishedMetaObject,
        thunk_igPsx2MultiTextureExt_GetMetaObject,
        igPsx2MultiTextureExt_className,
        0x34, /* instance size */
        igPsx2MultiTextureExt_GetVTable,
        &igPsx2MultiTextureExt_InitFields,
        0, /* extra callback item */
        g_igPsx2MultiTextureExt_callbackList /* callback list */
    );
}
