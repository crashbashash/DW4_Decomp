extern char igContextExt_GetPublishedMetaObject[];
extern char igPointSpriteExt_GetVTable[];
extern char thunk_igPointSpriteExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char g_igPointSpriteExt_callbackList[];
extern char igPointSpriteExt_className[];
extern char g_igPointSpriteExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPointSpriteExt_InitFields();

void igPointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPointSpriteExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igPointSpriteExt_GetMetaObject,
        igPointSpriteExt_className,
        0x188, /* instance size */
        igPointSpriteExt_GetVTable,
        &igPointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPointSpriteExt_callbackList /* callback list */
    );
}
