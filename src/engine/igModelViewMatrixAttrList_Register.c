/* 0x00135630 igModelViewMatrixAttrList_Register: registers class igModelViewMatrixAttrList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igModelViewMatrixAttrList_GetVTable[];
extern char thunk_igModelViewMatrixAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igModelViewMatrixAttrList_callbackList[];
extern char igModelViewMatrixAttrList_className[];
extern char g_igModelViewMatrixAttrList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igModelViewMatrixAttrList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixAttrList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                           /* base class registrar */
        igObjectList_GetPublishedMetaObject,             /* base class MetaObject accessor */
        thunk_igModelViewMatrixAttrList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igModelViewMatrixAttrList_className,  /* class name */
        0x14,                                            /* instance size */
        igModelViewMatrixAttrList_GetVTable,             /* vtable getter */
        0,                                               /* field adder */
        0,                                               /* extra callback item */
        g_igModelViewMatrixAttrList_callbackList  /* callback list */
    );
}
