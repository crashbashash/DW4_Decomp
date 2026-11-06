/* 0x0019cb20 igNodeListList_Register: registers class igNodeListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igNodeListList_GetVTable[];
extern char thunk_igNodeListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igNodeListList_callbackList[];
extern char igNodeListList_className[];
extern char g_igNodeListList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNodeListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNodeListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igNodeListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igNodeListList_className,  /* class name */
        0x14,                                 /* instance size */
        igNodeListList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igNodeListList_callbackList  /* callback list */
    );
}
