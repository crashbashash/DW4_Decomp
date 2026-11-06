/* 0x0013acc0 igAttrListList_Register: registers class igAttrListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrListList_GetVTable[];
extern char thunk_igAttrListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrListList_callbackList[];
extern char igAttrListList_className[];
extern char g_igAttrListList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igAttrListList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igAttrListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAttrListList_className,  /* class name */
        0x14,                                 /* instance size */
        igAttrListList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igAttrListList_callbackList  /* callback list */
    );
}
