/* 0x00451a40 igDefaultAspectElementList_Register: registers class igDefaultAspectElementList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDefaultAspectElementList_GetVTable[];
extern char thunk_igDefaultAspectElementList_GetMetaObject[];
extern char g_igDefaultAspectElementList_callbackList_004d0780[];
extern char s_igDefaultAspectElementList_className_0051e5f0[];
extern char g_igDefaultAspectElementList_metaObject_0058c5a0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igDefaultAspectElementList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultAspectElementList_metaObject_0058c5a0, /* published MetaObject slot */
        igObjectList_Register,                            /* base class registrar */
        igObjectList_GetPublishedMetaObject,              /* base class MetaObject accessor */
        thunk_igDefaultAspectElementList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDefaultAspectElementList_className_0051e5f0,  /* class name */
        0x14,                                             /* instance size */
        igDefaultAspectElementList_GetVTable,             /* vtable getter */
        0,                                                /* field adder */
        0,                                                /* extra callback item */
        g_igDefaultAspectElementList_callbackList_004d0780  /* callback list */
    );
}
