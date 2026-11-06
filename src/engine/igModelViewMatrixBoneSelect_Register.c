/* 0x0019d500 igModelViewMatrixBoneSelect_Register: registers class igModelViewMatrixBoneSelect with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igModelViewMatrixBoneSelect_GetVTable[];
extern char thunk_igModelViewMatrixBoneSelect_GetMetaObject[];
extern char igGroup_Register[];
extern char igModelViewMatrixBoneSelect_className[];
extern char g_igModelViewMatrixBoneSelect_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igModelViewMatrixBoneSelect_InitFields();

void igModelViewMatrixBoneSelect_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixBoneSelect_metaObject, /* published MetaObject slot */
        igGroup_Register,                                  /* base class registrar */
        igGroup_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igModelViewMatrixBoneSelect_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igModelViewMatrixBoneSelect_className,  /* class name */
        0x24,                                              /* instance size */
        igModelViewMatrixBoneSelect_GetVTable,             /* vtable getter */
        &igModelViewMatrixBoneSelect_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
