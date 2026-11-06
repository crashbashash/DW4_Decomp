extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igDisableExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char igDisableExt_className[];
extern char g_igDisableExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igDisableExt_SetAbstractProxy_0014f8a0[4];
void igDisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDisableExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igDisableExt_GetMetaObject,
        igDisableExt_className,
        0x14, /* instance size */
        0,
        &igDisableExt_SetAbstractProxy_0014f8a0[0],   /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}
