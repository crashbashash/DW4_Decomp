extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igPrimLengthArray_GetMetaObject[];
extern char igObject_Register[];
extern char igPrimLengthArray_className[];
extern char g_igPrimLengthArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPrimLengthArray_InitFields();

void igPrimLengthArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igPrimLengthArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPrimLengthArray_GetMetaObject,
        igPrimLengthArray_className,
        0x14, /* instance size */
        0,
        &igPrimLengthArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
