/* 0x00137b90 igGenericAttrDefaultManager_Register: registers class igGenericAttrDefaultManager with the object system, derived from igAttrDefaultManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttrDefaultManager_GetPublishedMetaObject[];
extern char igGenericAttrDefaultManager_GetVTable[];
extern char thunk_igGenericAttrDefaultManager_GetMetaObject[];
extern char igAttrDefaultManager_Register[];
extern char igGenericAttrDefaultManager_className[];
extern char g_igGenericAttrDefaultManager_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGenericAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGenericAttrDefaultManager_metaObject,    /* published MetaObject slot */
        igAttrDefaultManager_Register,                        /* base class registrar */
        igAttrDefaultManager_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGenericAttrDefaultManager_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igGenericAttrDefaultManager_className,     /* class name */
        8,                                                    /* instance size */
        igGenericAttrDefaultManager_GetVTable,                /* vtable getter */
        0,                                                    /* field adder */
        0,                                                    /* extra callback item */
        0                                                     /* callback list */
    );
}
