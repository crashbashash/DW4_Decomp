/* 0x001a5ea0 igAttrSet_Register: registers class igAttrSet with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igAttrSet_GetVTable[];
extern char thunk_igAttrSet_GetMetaObject[];
extern char g_igAttrSet_callbackList[];
extern char igAttrSet_className[];
extern char g_igAttrSet_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAttrSet_InitFields();

void igAttrSet_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrSet_metaObject,         /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAttrSet_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igAttrSet_className,          /* class name */
        0x28,                                    /* instance size */
        igAttrSet_GetVTable,                     /* vtable getter */
        &igAttrSet_InitFields,                   /* field adder */
        0,                                       /* extra callback item */
        g_igAttrSet_callbackList        /* callback list */
    );
}
