/* 0x002be1f0 igNamedObjectList_Register: registers class igNamedObjectList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igNamedObjectList_GetVTable[];
extern char thunk_igNamedObjectList_GetMetaObject[];
extern char g_igNamedObjectList_callbackList_004bfbd0[];
extern char s_igNamedObjectList_className_004f6580[];
extern char g_igNamedObjectList_metaObject_00585bd0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igNamedObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNamedObjectList_metaObject_00585bd0, /* published MetaObject slot */
        igObjectList_Register,                   /* base class registrar */
        igObjectList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igNamedObjectList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igNamedObjectList_className_004f6580,  /* class name */
        0x14,                                    /* instance size */
        igNamedObjectList_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        g_igNamedObjectList_callbackList_004bfbd0  /* callback list */
    );
}
