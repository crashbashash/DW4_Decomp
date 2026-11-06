/* 0x00451a40 igDefaultAspectElementList_Register: registers class igDefaultAspectElementList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDefaultAspectElementList_GetVTable[];
extern char thunk_igDefaultAspectElementList_GetMetaObject[];
extern char g_igDefaultAspectElementList_callbackList[];
extern char igDefaultAspectElementList_className[];
extern char g_igDefaultAspectElementList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igDefaultAspectElementList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultAspectElementList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                            /* base class registrar */
        igObjectList_GetPublishedMetaObject,              /* base class MetaObject accessor */
        thunk_igDefaultAspectElementList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDefaultAspectElementList_className,  /* class name */
        0x14,                                             /* instance size */
        igDefaultAspectElementList_GetVTable,             /* vtable getter */
        0,                                                /* field adder */
        0,                                                /* extra callback item */
        g_igDefaultAspectElementList_callbackList  /* callback list */
    );
}
