extern char igImageConvert_Register[];
extern char thunk_igPsx2ImageConvert_GetMetaObject[];
extern char igPsx2ImageConvert_GetVTable[];
extern char igImageConvert_GetPublishedMetaObject[];
extern char igPsx2ImageConvert_className[];
extern char g_igPsx2ImageConvert_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2ImageConvert_InitFields_00153d10[4];
void igPsx2ImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ImageConvert_metaObject,
        igImageConvert_Register,
        igImageConvert_GetPublishedMetaObject,
        thunk_igPsx2ImageConvert_GetMetaObject,
        igPsx2ImageConvert_className,
        8, /* instance size */
        igPsx2ImageConvert_GetVTable,
        &igPsx2ImageConvert_InitFields_00153d10[0],     /* Field adder. */
        0,                                              /* extra callback-vector item (none) */
        0                                               /* zero-terminated callback-vector item list (none) */
    );
}
