/* 0x001a2650 igCompressedTransformSequence1_5Data_Register: registers class igCompressedTransformSequence1_5Data with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompressedTransformSequence1_5Data_GetVTable[];
extern char thunk_igCompressedTransformSequence1_5Data_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCompressedTransformSequence1_5Data_callbackList_0048c418[];
extern char s_igCompressedTransformSequence1_5Data_className_004e2b70[];
extern char g_igCompressedTransformSequence1_5Data_metaObject_00561be0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igCompressedTransformSequence1_5Data_InitFields();

void igCompressedTransformSequence1_5Data_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompressedTransformSequence1_5Data_metaObject_00561be0, /* published MetaObject slot */
        igObject_Register,                                          /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,                      /* base class MetaObject accessor */
        thunk_igCompressedTransformSequence1_5Data_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCompressedTransformSequence1_5Data_className_004e2b70,  /* class name */
        0x30,                                                       /* instance size */
        igCompressedTransformSequence1_5Data_GetVTable,             /* vtable getter */
        &igCompressedTransformSequence1_5Data_InitFields,           /* field adder */
        0,                                                          /* extra callback item */
        g_igCompressedTransformSequence1_5Data_callbackList_0048c418  /* callback list */
    );
}
