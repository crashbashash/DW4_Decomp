/* 0x00450d60 igFieldChangeViewList_Register: registers class igFieldChangeViewList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igFieldChangeViewList_GetVTable[];
extern char thunk_igFieldChangeViewList_GetMetaObject[];
extern char g_igFieldChangeViewList_callbackList[];
extern char igFieldChangeViewList_className[];
extern char g_igFieldChangeViewList_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igFieldChangeViewList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFieldChangeViewList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                       /* base class registrar */
        igObjectList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igFieldChangeViewList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igFieldChangeViewList_className,  /* class name */
        0x14,                                        /* instance size */
        igFieldChangeViewList_GetVTable,             /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igFieldChangeViewList_callbackList  /* callback list */
    );
}
