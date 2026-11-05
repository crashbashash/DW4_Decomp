/* 0x001a4980 igBoundingBoxesMaker_Register: registers class igBoundingBoxesMaker with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoundingBoxesMaker_GetVTable[];
extern char thunk_igBoundingBoxesMaker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBoundingBoxesMaker_callbackList_0048cab0[];
extern char s_igBoundingBoxesMaker_className_004e3300[];
extern char g_igBoundingBoxesMaker_metaObject_00561ef0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igBoundingBoxesMaker_InitFields();

void igBoundingBoxesMaker_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoundingBoxesMaker_metaObject_00561ef0, /* published MetaObject slot */
        igObject_Register,                          /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,      /* base class MetaObject accessor */
        thunk_igBoundingBoxesMaker_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igBoundingBoxesMaker_className_004e3300,  /* class name */
        0x28,                                       /* instance size */
        igBoundingBoxesMaker_GetVTable,             /* vtable getter */
        &igBoundingBoxesMaker_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igBoundingBoxesMaker_callbackList_0048cab0  /* callback list */
    );
}
