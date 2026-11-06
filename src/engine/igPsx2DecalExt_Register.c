extern char igDecalExt_Register[];
extern char thunk_igPsx2DecalExt_GetMetaObject[];
extern char igPsx2DecalExt_GetVTable[];
extern char igDecalExt_GetPublishedMetaObject[];
extern char g_igPsx2DecalExt_callbackList[];
extern char igPsx2DecalExt_className[];
extern char g_igPsx2DecalExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2DecalExt_InitFields();

void igPsx2DecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2DecalExt_metaObject,
        igDecalExt_Register,
        igDecalExt_GetPublishedMetaObject,
        thunk_igPsx2DecalExt_GetMetaObject,
        igPsx2DecalExt_className,
        0x20, /* instance size */
        igPsx2DecalExt_GetVTable,
        &igPsx2DecalExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DecalExt_callbackList /* callback list */
    );
}
