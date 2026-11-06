extern char igUserUCodeExt_Register[];
extern char thunk_igPsx2UserUCodeExt_GetMetaObject[];
extern char igPsx2UserUCodeExt_GetVTable[];
extern char igUserUCodeExt_GetPublishedMetaObject[];
extern char g_igPsx2UserUCodeExt_callbackList[];
extern char igPsx2UserUCodeExt_className[];
extern char g_igPsx2UserUCodeExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2UserUCodeExt_InitFields();

void igPsx2UserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2UserUCodeExt_metaObject,
        igUserUCodeExt_Register,
        igUserUCodeExt_GetPublishedMetaObject,
        thunk_igPsx2UserUCodeExt_GetMetaObject,
        igPsx2UserUCodeExt_className,
        0x24, /* instance size */
        igPsx2UserUCodeExt_GetVTable,
        &igPsx2UserUCodeExt_InitFields,
        0, /* extra callback item */
        g_igPsx2UserUCodeExt_callbackList /* callback list */
    );
}
