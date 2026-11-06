/* 0x0023ab00 igBoundingSphereMaker_Register: registers class igBoundingSphereMaker with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoundingSphereMaker_GetVTable[];
extern char thunk_igBoundingSphereMaker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBoundingSphereMaker_callbackList[];
extern char igBoundingSphereMaker_className[];
extern char g_igBoundingSphereMaker_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBoundingSphereMaker_InitFields();

void igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoundingSphereMaker_metaObject, /* published MetaObject slot */
        igObject_Register,                           /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,       /* base class MetaObject accessor */
        thunk_igBoundingSphereMaker_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igBoundingSphereMaker_className,  /* class name */
        0xC,                                         /* instance size */
        igBoundingSphereMaker_GetVTable,             /* vtable getter */
        &igBoundingSphereMaker_InitFields,           /* field adder */
        0,                                           /* extra callback item */
        g_igBoundingSphereMaker_callbackList  /* callback list */
    );
}
