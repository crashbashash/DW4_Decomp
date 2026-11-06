extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igModelViewMatrixAttr_GetVTable[];
extern char thunk_igModelViewMatrixAttr_GetMetaObject[];
void FUN_00135980(void);
extern char igModelViewMatrixAttr_className[];
extern char g_igModelViewMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igModelViewMatrixAttr_InitFields();

void igModelViewMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttr_GetMetaObject,
        igModelViewMatrixAttr_className,
        0x4C,                                              /* instance size (the reflected struct is shorter: igMatrix44f is reflected as one int) */
        igModelViewMatrixAttr_GetVTable,
        &igModelViewMatrixAttr_InitFields,
        FUN_00135980,                                      /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}
