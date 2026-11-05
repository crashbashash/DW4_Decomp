/* 0x00195c10 igTransformRecorder_Register: registers class igTransformRecorder with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igTransformRecorder_GetVTable[];
extern char thunk_igTransformRecorder_GetMetaObject[];
extern char igGroup_Register[];
extern char s_igTransformRecorder_className_004e1520[];
extern char g_igTransformRecorder_metaObject_00561280[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTransformRecorder_InitFields();

void igTransformRecorder_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformRecorder_metaObject_00561280, /* published MetaObject slot */
        igGroup_Register,                          /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0,   /* base class MetaObject accessor */
        thunk_igTransformRecorder_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igTransformRecorder_className_004e1520,  /* class name */
        0xA0,                                      /* instance size */
        igTransformRecorder_GetVTable,             /* vtable getter */
        &igTransformRecorder_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
