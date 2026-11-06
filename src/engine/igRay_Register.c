extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRay_GetVTable[];
extern char thunk_igRay_GetMetaObject[];
extern char igObject_Register[];
extern char igRay_className[];
extern char g_igRay_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igRay_InitFields();

void igRay_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRay_GetMetaObject,
        igRay_className,
        0x24, /* instance size */
        igRay_GetVTable,
        &igRay_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
