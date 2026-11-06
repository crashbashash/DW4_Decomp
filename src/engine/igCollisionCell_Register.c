/* 0x0023a860 igCollisionCell_Register: registers class igCollisionCell with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionCell_GetVTable[];
extern char thunk_igCollisionCell_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionCell_callbackList[];
extern char igCollisionCell_className[];
extern char g_igCollisionCell_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionCell_InitFields();

void igCollisionCell_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionCell_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igCollisionCell_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCollisionCell_className,  /* class name */
        0x20,                                  /* instance size */
        igCollisionCell_GetVTable,             /* vtable getter */
        &igCollisionCell_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igCollisionCell_callbackList  /* callback list */
    );
}
