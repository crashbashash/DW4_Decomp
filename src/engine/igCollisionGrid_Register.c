/* 0x0023a350 igCollisionGrid_Register: registers class igCollisionGrid with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionGrid_GetVTable[];
extern char thunk_igCollisionGrid_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionGrid_callbackList_00498470[];
extern char s_igCollisionGrid_className_004ea020[];
extern char g_igCollisionGrid_metaObject_0056dd40[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCollisionGrid_InitFields();

void igCollisionGrid_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionGrid_metaObject_0056dd40, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igCollisionGrid_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionGrid_className_004ea020,  /* class name */
        0x4C,                                  /* instance size */
        igCollisionGrid_GetVTable,             /* vtable getter */
        &igCollisionGrid_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igCollisionGrid_callbackList_00498470  /* callback list */
    );
}
