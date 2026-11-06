/* 0x0019d370 igModelViewMatrixBoneSelectList_561880_Register: registers class igModelViewMatrixBoneSelectList_561880 with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igModelViewMatrixBoneSelectList_561880_GetVTable[];
extern char thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igModelViewMatrixBoneSelectList_561880_callbackList[];
extern char igModelViewMatrixBoneSelectList_className[];
extern char g_igModelViewMatrixBoneSelectList_metaObject_00561880[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igModelViewMatrixBoneSelectList_561880_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixBoneSelectList_metaObject_00561880,      /* published MetaObject slot */
        igObjectList_Register,                                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,                        /* base class MetaObject accessor */
        thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject, /* own MetaObject accessor (stored at +0x54) */
        igModelViewMatrixBoneSelectList_className,       /* class name */
        0x14,                                                       /* instance size */
        igModelViewMatrixBoneSelectList_561880_GetVTable,           /* vtable getter */
        0,                                                          /* field adder */
        0,                                                          /* extra callback item */
        g_igModelViewMatrixBoneSelectList_561880_callbackList  /* callback list */
    );
}
