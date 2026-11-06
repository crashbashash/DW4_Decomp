/* 0x002b8480 igThreadList_Register: registers class igThreadList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igThreadList_GetVTable[];
extern char thunk_igThreadList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igThreadList_callbackList[];
extern char igThreadList_className[];
extern char g_igThreadList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igThreadList_metaObject,  /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igThreadList_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igThreadList_className,   /* class name */
        0x14,                                /* instance size */
        igThreadList_GetVTable,              /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igThreadList_callbackList  /* callback list */
    );
}
