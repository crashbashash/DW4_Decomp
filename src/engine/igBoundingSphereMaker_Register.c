/* 0x0023ab00 igBoundingSphereMaker_Register: registers class igBoundingSphereMaker with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoundingSphereMaker_GetVTable[];
extern char thunk_igBoundingSphereMaker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBoundingSphereMaker_callbackList_00498618[];
extern char s_igBoundingSphereMaker_className_004ea160[];
extern char g_igBoundingSphereMaker_metaObject_0056de00[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igBoundingSphereMaker_InitFields();

void igBoundingSphereMaker_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoundingSphereMaker_metaObject_0056de00, /* published MetaObject slot */
        igObject_Register,                           /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,       /* base class MetaObject accessor */
        thunk_igBoundingSphereMaker_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igBoundingSphereMaker_className_004ea160,  /* class name */
        0xC,                                         /* instance size */
        igBoundingSphereMaker_GetVTable,             /* vtable getter */
        &igBoundingSphereMaker_InitFields,           /* field adder */
        0,                                           /* extra callback item */
        g_igBoundingSphereMaker_callbackList_00498618  /* callback list */
    );
}
