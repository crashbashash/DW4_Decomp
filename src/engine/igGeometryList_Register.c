/* 0x0019fa20 igGeometryList_Register: registers class igGeometryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igGeometryList_GetVTable[];
extern char thunk_igGeometryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGeometryList_callbackList[];
extern char igGeometryList_className[];
extern char g_igGeometryList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igGeometryList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igGeometryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGeometryList_className,  /* class name */
        0x14,                                 /* instance size */
        igGeometryList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igGeometryList_callbackList  /* callback list */
    );
}
