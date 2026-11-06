/* 0x001a4680 igCamera_Register: registers class igCamera with the object system, derived from igNode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNode_Register[];
extern char igNode_GetPublishedMetaObject[];
extern char igCamera_GetVTable[];
extern char thunk_igCamera_GetMetaObject[];
extern char igCamera_className[];
extern char g_igCamera_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igCamera_InitFields();

void igCamera_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCamera_metaObject,         /* published MetaObject slot */
        igNode_Register,                        /* base class registrar */
        igNode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCamera_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igCamera_className,          /* class name */
        0x38,                                   /* instance size */
        igCamera_GetVTable,                     /* vtable getter */
        &igCamera_InitFields,                   /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
