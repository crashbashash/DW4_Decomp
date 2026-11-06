extern char igMemoryImage_Register[];
extern char thunk_igPsx2Image_GetMetaObject[];
extern char igPsx2Image_GetVTable[];
extern char igMemoryImage_GetPublishedMetaObject[];
extern char igPsx2Image_className[];
extern char g_igPsx2Image_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2Image_InitFields_00153ef0[4];
void igPsx2Image_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Image_metaObject,
        igMemoryImage_Register,
        igMemoryImage_GetPublishedMetaObject,
        thunk_igPsx2Image_GetMetaObject,
        igPsx2Image_className,
        0x5C, /* instance size */
        igPsx2Image_GetVTable,
        &igPsx2Image_InitFields_00153ef0[0],           /* Field adder. */
        0,                                             /* extra callback-vector item (none) */
        0                                              /* zero-terminated callback-vector item list (none) */
    );
}
