extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igCustomState_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igCustomState_className[];
extern char g_igCustomState_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomState_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igCustomState_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igCustomState_GetMetaObject,
        igCustomState_className,
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
