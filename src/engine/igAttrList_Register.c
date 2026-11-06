/* 0x0013aff0 igAttrList_Register: registers class igAttrList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrList_GetVTable[];
extern char thunk_igAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrList_callbackList[];
extern char igAttrList_className[];
extern char g_igAttrList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igAttrList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrList_metaObject,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAttrList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igAttrList_className,     /* class name */
        0x14,                                /* instance size */
        igAttrList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igAttrList_callbackList   /* callback list */
    );
}
