/* 0x0013ab60 igAttrDefaultManager_Register: registers class igAttrDefaultManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAttrDefaultManager_GetMetaObject[];
extern char igObject_Register[];
extern char igAttrDefaultManager_className[];
extern char g_igAttrDefaultManager_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrDefaultManager_metaObject, /* published MetaObject slot */
        igObject_Register,                          /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,      /* base class MetaObject accessor */
        thunk_igAttrDefaultManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAttrDefaultManager_className,  /* class name */
        8,                                          /* instance size */
        0,                                          /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
