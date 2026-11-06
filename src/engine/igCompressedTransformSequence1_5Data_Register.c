extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompressedTransformSequence1_5Data_GetVTable[];
extern char thunk_igCompressedTransformSequence1_5Data_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCompressedTransformSequence1_5Data_callbackList[];
extern char igCompressedTransformSequence1_5Data_className[];
extern char g_igCompressedTransformSequence1_5Data_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompressedTransformSequence1_5Data_InitFields();

void igCompressedTransformSequence1_5Data_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompressedTransformSequence1_5Data_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompressedTransformSequence1_5Data_GetMetaObject,
        igCompressedTransformSequence1_5Data_className,
        0x30, /* instance size */
        igCompressedTransformSequence1_5Data_GetVTable,
        &igCompressedTransformSequence1_5Data_InitFields,
        0, /* extra callback item */
        g_igCompressedTransformSequence1_5Data_callbackList /* callback list */
    );
}
