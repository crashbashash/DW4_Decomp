extern char igClut_Register[];
extern char thunk_igPsx2Clut_GetMetaObject[];
extern char igPsx2Clut_GetVTable[];
extern char igClut_GetPublishedMetaObject[];
extern char igPsx2Clut_className[];
extern char g_igPsx2Clut_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2Clut_InitFields();

void igPsx2Clut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Clut_metaObject,
        igClut_Register,
        igClut_GetPublishedMetaObject,
        thunk_igPsx2Clut_GetMetaObject,
        igPsx2Clut_className,
        0x28, /* instance size */
        igPsx2Clut_GetVTable,
        &igPsx2Clut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
