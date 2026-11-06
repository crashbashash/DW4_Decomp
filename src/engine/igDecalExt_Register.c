extern char igContextExt_GetPublishedMetaObject[];
void thunk_FUN_0014f8d0(void);
extern char igContextExt_Register[];
extern char igDecalExt_className[];
extern char g_igDecalExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igDecalExt_InitFields();

void igDecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDecalExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_FUN_0014f8d0,
        igDecalExt_className,
        0x18, /* instance size */
        0,
        &igDecalExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
