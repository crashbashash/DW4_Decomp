extern char igPointSpriteExt_Register[];
extern char thunk_igPsx2PointSpriteExt_GetMetaObject[];
extern char igPsx2PointSpriteExt_GetVTable[];
extern char igPointSpriteExt_GetPublishedMetaObject[];
extern char g_igPsx2PointSpriteExt_callbackList[];
extern char igPsx2PointSpriteExt_className[];
extern char g_igPsx2PointSpriteExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2PointSpriteExt_InitFields();

void igPsx2PointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2PointSpriteExt_metaObject,
        igPointSpriteExt_Register,
        igPointSpriteExt_GetPublishedMetaObject,
        thunk_igPsx2PointSpriteExt_GetMetaObject,
        igPsx2PointSpriteExt_className,
        0x18C, /* instance size */
        igPsx2PointSpriteExt_GetVTable,
        &igPsx2PointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPsx2PointSpriteExt_callbackList /* callback list */
    );
}
