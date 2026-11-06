extern char thunk_igVisualAttribute_GetMetaObject[];
extern char igAttr_GetPublishedMetaObject[];
extern char igAttr_Register[];
extern char igVisualAttribute_className[];
extern char g_igVisualAttribute_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igVisualAttribute_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVisualAttribute_metaObject,
        igAttr_Register,
        igAttr_GetPublishedMetaObject,
        thunk_igVisualAttribute_GetMetaObject,
        igVisualAttribute_className,
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
