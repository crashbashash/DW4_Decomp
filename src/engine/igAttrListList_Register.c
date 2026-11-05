/* 0x0013acc0 igAttrListList_Register: registers class igAttrListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrListList_GetVTable[];
extern char thunk_igAttrListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrListList_callbackList_00486c38[];
extern char s_igAttrListList_className_004d5d28[];
extern char g_igAttrListList_metaObject_0055f450[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igAttrListList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrListList_metaObject_0055f450, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igAttrListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAttrListList_className_004d5d28,  /* class name */
        0x14,                                 /* instance size */
        igAttrListList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igAttrListList_callbackList_00486c38  /* callback list */
    );
}
