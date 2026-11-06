/* 0x002bdfd0 igNamedObjectInfo_Register: registers class igNamedObjectInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject[];
extern char igNamedObjectInfo_GetVTable[];
extern char thunk_igNamedObjectInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igNamedObjectInfo_callbackList[];
extern char igNamedObjectInfo_className[];
extern char g_igNamedObjectInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igNamedObjectInfo_InitFields();

void igNamedObjectInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNamedObjectInfo_metaObject, /* published MetaObject slot */
        igInfo_Register,                         /* base class registrar */
        igInfo_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igNamedObjectInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igNamedObjectInfo_className,  /* class name */
        0x18,                                    /* instance size */
        igNamedObjectInfo_GetVTable,             /* vtable getter */
        &igNamedObjectInfo_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igNamedObjectInfo_callbackList  /* callback list */
    );
}
