/* 0x001a2da0 igBlendListRecord_Register: registers class igBlendListRecord with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBlendListRecord_GetVTable[];
extern char thunk_igBlendListRecord_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBlendListRecord_callbackList[];
extern char igBlendListRecord_className[];
extern char g_igBlendListRecord_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igBlendListRecord_InitFields();

void igBlendListRecord_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendListRecord_metaObject, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igBlendListRecord_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igBlendListRecord_className,  /* class name */
        0x10,                                    /* instance size */
        igBlendListRecord_GetVTable,             /* vtable getter */
        &igBlendListRecord_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igBlendListRecord_callbackList  /* callback list */
    );
}
