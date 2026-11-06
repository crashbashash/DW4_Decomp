extern char thunk_igUserUCodeExt_GetMetaObject[];
extern char igContextExt_GetPublishedMetaObject[];
extern char igContextExt_Register[];
extern char igUserUCodeExt_className[];
extern char g_igUserUCodeExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
void FUN_0014bc50(void);
void igUserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igUserUCodeExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igUserUCodeExt_GetMetaObject,
        igUserUCodeExt_className,
        0x14, /* instance size */
        0,
        FUN_0014bc50,
        0, /* extra callback item */
        0 /* callback list */
    );
}
