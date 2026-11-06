extern char igVec4ucMetaField_GetVTable[];
extern char thunk_igVec4ucMetaField_GetMetaObject_00187170[];
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec4ucMetaField_callbackList[];
extern char igVec4ucMetaField_className[];
extern char g_igVec4ucMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec4ucMetaField_Register(void) {
    FUN_00186a40();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4ucMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec4ucMetaField_GetMetaObject_00187170,
        igVec4ucMetaField_className,
        0x34, /* instance size */
        igVec4ucMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec4ucMetaField_callbackList /* callback list */
    );
}
