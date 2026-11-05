/* 0x001964e0 igTransform_Register: registers class igTransform with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igTransform_GetVTable[];
extern char thunk_igTransform_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igTransform_callbackList_0048b178[];
extern char s_igTransform_className_004e1598[];
extern char g_igTransform_metaObject_005612b0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTransform_InitFields();

void igTransform_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransform_metaObject_005612b0,       /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igTransform_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igTransform_className_004e1598,        /* class name */
        0x6C,                                    /* instance size */
        igTransform_GetVTable,                   /* vtable getter */
        &igTransform_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        g_igTransform_callbackList_0048b178      /* callback list */
    );
}
