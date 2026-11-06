extern char igTimer_Register[];
extern char thunk_igLongTimer_GetMetaObject_002b7b60[];
extern char igTimer_GetPublishedMetaObject[];
extern char igLongTimer_className[];
extern char g_igLongTimer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLongTimer_InitFields();

void igLongTimer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLongTimer_metaObject,
        igTimer_Register,
        igTimer_GetPublishedMetaObject,
        thunk_igLongTimer_GetMetaObject_002b7b60,
        igLongTimer_className,
        0x28, /* instance size */
        0,
        &igLongTimer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
