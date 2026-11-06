/* 0x002bc850 igPluginRepositoryList_Register: registers class igPluginRepositoryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igPluginRepositoryList_GetVTable[];
extern char thunk_igPluginRepositoryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igPluginRepositoryList_callbackList[];
extern char igPluginRepositoryList_className[];
extern char g_igPluginRepositoryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPluginRepositoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPluginRepositoryList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                        /* base class registrar */
        igObjectList_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igPluginRepositoryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igPluginRepositoryList_className,  /* class name */
        0x14,                                         /* instance size */
        igPluginRepositoryList_GetVTable,             /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igPluginRepositoryList_callbackList  /* callback list */
    );
}
