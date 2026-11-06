/* 0x0014be80 igPrimLengthArray1_1_Register: registers class igPrimLengthArray1_1 with the object system, derived from igPrimLengthArray.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
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
    FUN_00149bc0();  /* set-once guard that first runs the sibling registrars it chains to (asm/FUN_00149bc0.s) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPrimLengthArray1_1_metaObject,        /* published MetaObject slot */
        igPrimLengthArray_Register,                        /* base class registrar */
        igPrimLengthArray_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_0014bde0,                                      /* own MetaObject accessor (stored at +0x54) */
        igPrimLengthArray1_1_className,         /* class name */
        0x14,                                              /* instance size */
        igPrimLengthArray1_1_GetVTable,                    /* vtable getter */
        &igPrimLengthArray1_1_InitFields,                  /* field adder */
        0,                                                 /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}
