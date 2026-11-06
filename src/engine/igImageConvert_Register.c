extern char igImageUtils_GetPublishedMetaObject[];
extern char thunk_igImageConvert_GetMetaObject[];
extern char igImageUtils_Register[];
extern char igImageConvert_className[];
extern char g_igImageConvert_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igImageConvert_SetAbstractProxy_0014dc40[4];
void igImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageConvert_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        thunk_igImageConvert_GetMetaObject,
        igImageConvert_className,
        8, /* instance size */
        0,
        &igImageConvert_SetAbstractProxy_0014dc40[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}
