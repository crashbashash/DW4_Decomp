/* 0x0023a860 igCollisionCell_Register: registers class igCollisionCell with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionCell_GetVTable[];
extern char thunk_igCollisionCell_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionCell_callbackList_00498590[];
extern char s_igCollisionCell_className_004ea110[];
extern char g_igCollisionCell_metaObject_0056ddc8[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCollisionCell_InitFields();

void igCollisionCell_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionCell_metaObject_0056ddc8, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igCollisionCell_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionCell_className_004ea110,  /* class name */
        0x20,                                  /* instance size */
        igCollisionCell_GetVTable,             /* vtable getter */
        &igCollisionCell_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igCollisionCell_callbackList_00498590  /* callback list */
    );
}
