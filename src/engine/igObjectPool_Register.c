/* 0x001967d0 igObjectPool_Register: registers class igObjectPool with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectPool_GetVTable[];
extern char thunk_igObjectPool_GetMetaObject[];
extern char igObjectList_Register[];
extern char igObjectPool_className[];
extern char g_igObjectPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igObjectPool_InitFields();

void igObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectPool_metaObject,  /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igObjectPool_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igObjectPool_className,   /* class name */
        0x20,                                /* instance size */
        igObjectPool_GetVTable,              /* vtable getter */
        &igObjectPool_InitFields,            /* field adder */
        0,                                   /* extra callback item */
        0                                    /* callback list */
    );
}
