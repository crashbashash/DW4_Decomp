extern char igMetaField_GetPublishedMetaObject[];
extern char igStructMetaField_GetVTable[];
extern char thunk_igStructMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igStructMetaField_callbackList[];
extern char igStructMetaField_className[];
extern char g_igStructMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igStructMetaField_InitFields_002b8b50[4];
void igStructMetaField_Register(void) {
    FUN_002b5d50();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStructMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igStructMetaField_GetMetaObject,
        igStructMetaField_className,
        0x40, /* instance size */
        igStructMetaField_GetVTable,
        &igStructMetaField_InitFields_002b8b50[0],                            /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igStructMetaField_callbackList /* callback list */
    );
}
