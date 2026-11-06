extern char igIndexArray_Register[];
extern char thunk_igPsx2IndexArray_GetMetaObject[];
extern char igPsx2IndexArray_GetVTable[];
extern char igIndexArray_GetPublishedMetaObject[];
extern char igPsx2IndexArray_className[];
extern char g_igPsx2IndexArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2IndexArray_InitFields_00153bd0[4];
void igPsx2IndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2IndexArray_metaObject,
        igIndexArray_Register,
        igIndexArray_GetPublishedMetaObject,
        thunk_igPsx2IndexArray_GetMetaObject,
        igPsx2IndexArray_className,
        0x1C, /* instance size */
        igPsx2IndexArray_GetVTable,
        &igPsx2IndexArray_InitFields_00153bd0[0],     /* Field adder. */
        0,                                            /* extra callback-vector item (none) */
        0                                             /* zero-terminated callback-vector item list (none) */
    );
}
