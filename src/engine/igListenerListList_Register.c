/* 0x002270c0 igListenerListList_Register: registers class igListenerListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igListenerListList_GetVTable[];
extern char thunk_igListenerListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igListenerListList_callbackList[];
extern char igListenerListList_className[];
extern char g_igListenerListList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igListenerListList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igListenerListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igListenerListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igListenerListList_className,  /* class name */
        0x14,                                     /* instance size */
        igListenerListList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igListenerListList_callbackList  /* callback list */
    );
}
