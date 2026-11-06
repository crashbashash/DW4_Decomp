/* 0x002c6900 igDriverDatabase_Register: registers class igDriverDatabase with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDriverDatabase_GetVTable[];
extern char thunk_igDriverDatabase_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDriverDatabase_callbackList[];
extern char igDriverDatabase_className[];
extern char g_igDriverDatabase_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDriverDatabase_InitFields();

void igDriverDatabase_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDriverDatabase_metaObject, /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igDriverDatabase_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDriverDatabase_className,  /* class name */
        0x38,                                   /* instance size */
        igDriverDatabase_GetVTable,             /* vtable getter */
        &igDriverDatabase_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igDriverDatabase_callbackList  /* callback list */
    );
}
