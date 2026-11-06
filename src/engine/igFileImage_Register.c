extern char igImage_GetPublishedMetaObject[];
extern char thunk_igFileImage_GetMetaObject[];
extern char igImage_Register[];
extern char igFileImage_className[];
extern char g_igFileImage_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igFileImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFileImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        thunk_igFileImage_GetMetaObject,
        igFileImage_className,
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
