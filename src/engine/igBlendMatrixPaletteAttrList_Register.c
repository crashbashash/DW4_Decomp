/* 0x00139910 igBlendMatrixPaletteAttrList_Register: registers class igBlendMatrixPaletteAttrList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igBlendMatrixPaletteAttrList_GetVTable[];
extern char thunk_igBlendMatrixPaletteAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igBlendMatrixPaletteAttrList_callbackList[];
extern char igBlendMatrixPaletteAttrList_className[];
extern char g_igBlendMatrixPaletteAttrList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igBlendMatrixPaletteAttrList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatrixPaletteAttrList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                              /* base class registrar */
        igObjectList_GetPublishedMetaObject,                /* base class MetaObject accessor */
        thunk_igBlendMatrixPaletteAttrList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igBlendMatrixPaletteAttrList_className,  /* class name */
        0x14,                                               /* instance size */
        igBlendMatrixPaletteAttrList_GetVTable,             /* vtable getter */
        0,                                                  /* field adder */
        0,                                                  /* extra callback item */
        g_igBlendMatrixPaletteAttrList_callbackList  /* callback list */
    );
}
