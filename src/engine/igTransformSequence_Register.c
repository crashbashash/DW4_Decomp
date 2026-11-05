/* 0x00195590 igTransformSequence_Register: registers class igTransformSequence with the object system, derived from igTransformSource.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransformSource_Register[];
extern char thunk_igTransformSequence_GetMetaObject[];
extern char igTransformSource_GetPublishedMetaObject_00195610[];
extern char g_igTransformSequence_callbackList_0048b070[];
extern char s_igTransformSequence_className_004e1460[];
extern char g_igTransformSequence_metaObject_00561230[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTransformSequence_InitFields();

void igTransformSequence_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformSequence_metaObject_00561230,         /* published MetaObject slot */
        igTransformSource_Register,                        /* base class registrar */
        igTransformSource_GetPublishedMetaObject_00195610, /* base class MetaObject accessor */
        thunk_igTransformSequence_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igTransformSequence_className_004e1460,          /* class name */
        0x38,                                              /* instance size */
        0,                                                 /* vtable getter */
        &igTransformSequence_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        g_igTransformSequence_callbackList_0048b070        /* callback list */
    );
}
