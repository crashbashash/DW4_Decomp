/* 0x0014c0e0 igPrimLengthArray_Register: registers class igPrimLengthArray with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
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
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPrimLengthArray_metaObject, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igPrimLengthArray_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igPrimLengthArray_className,  /* class name */
        0x14,                                    /* instance size */
        0,                                       /* vtable getter */
        &igPrimLengthArray_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
