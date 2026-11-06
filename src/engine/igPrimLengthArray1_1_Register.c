extern char igPrimLengthArray1_1_GetVTable[];
void thunk_FUN_0014bde0(void);
extern char igPrimLengthArray_GetPublishedMetaObject[];
extern char igPrimLengthArray_Register[];
extern char igPrimLengthArray1_1_className[];
extern char g_igPrimLengthArray1_1_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPrimLengthArray1_1_InitFields();

void igPrimLengthArray1_1_Register(void) {
    FUN_00149bc0();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPrimLengthArray1_1_metaObject,
        igPrimLengthArray_Register,
        igPrimLengthArray_GetPublishedMetaObject,
        thunk_FUN_0014bde0,
        igPrimLengthArray1_1_className,
        0x14, /* instance size */
        igPrimLengthArray1_1_GetVTable,
        &igPrimLengthArray1_1_InitFields,
        0,                                                 /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}
