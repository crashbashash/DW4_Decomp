/* 0x001a5060 igBillboard_Register: registers class igBillboard with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igBillboard_GetVTable[];
extern char thunk_igBillboard_GetMetaObject[];
extern char g_igBillboard_callbackList[];
extern char igBillboard_className[];
extern char g_igBillboard_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBillboard_InitFields();

void igBillboard_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBillboard_metaObject,       /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBillboard_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igBillboard_className,        /* class name */
        0x40,                                    /* instance size */
        igBillboard_GetVTable,                   /* vtable getter */
        &igBillboard_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        g_igBillboard_callbackList      /* callback list */
    );
}
