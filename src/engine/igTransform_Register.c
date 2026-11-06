/* 0x001964e0 igTransform_Register: registers class igTransform with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igTransform_GetVTable[];
extern char thunk_igTransform_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igTransform_callbackList[];
extern char igTransform_className[];
extern char g_igTransform_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTransform_InitFields();

void igTransform_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransform_metaObject,       /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTransform_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igTransform_className,        /* class name */
        0x6C,                                    /* instance size */
        igTransform_GetVTable,                   /* vtable getter */
        &igTransform_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        g_igTransform_callbackList      /* callback list */
    );
}
