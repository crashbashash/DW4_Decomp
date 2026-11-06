extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igLineWidthExt_GetMetaObject_0014d750[];
extern char igContextExt_Register[];
extern char igLineWidthExt_className[];
extern char g_igLineWidthExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igLineWidthExt_InitFields();

void igLineWidthExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLineWidthExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igLineWidthExt_GetMetaObject_0014d750,
        igLineWidthExt_className,
        0x18, /* instance size */
        0,
        &igLineWidthExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
