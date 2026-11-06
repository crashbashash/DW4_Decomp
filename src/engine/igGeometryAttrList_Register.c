/* 0x0013a5c0 igGeometryAttrList_Register: registers class igGeometryAttrList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igGeometryAttrList_GetVTable[];
extern char thunk_igGeometryAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGeometryAttrList_callbackList[];
extern char igGeometryAttrList_className[];
extern char g_igGeometryAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGeometryAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryAttrList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igGeometryAttrList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGeometryAttrList_className,  /* class name */
        0x14,                                     /* instance size */
        igGeometryAttrList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igGeometryAttrList_callbackList  /* callback list */
    );
}
