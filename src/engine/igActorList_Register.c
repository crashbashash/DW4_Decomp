/* 0x001aa6b0 igActorList_Register: registers class igActorList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igActorList_GetVTable[];
extern char thunk_igActorList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igActorList_callbackList[];
extern char igActorList_className[];
extern char g_igActorList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igActorList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActorList_metaObject,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igActorList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igActorList_className,    /* class name */
        0x14,                                /* instance size */
        igActorList_GetVTable,               /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igActorList_callbackList  /* callback list */
    );
}
