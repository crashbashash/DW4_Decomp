/* 0x00197cd0 igRenderPackage_Register: registers class igRenderPackage with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRenderPackage_GetVTable[];
extern char thunk_igRenderPackage_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRenderPackage_callbackList_0048b4c0[];
extern char s_igRenderPackage_className_004e19e0[];
extern char g_igRenderPackage_metaObject_00561450[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igRenderPackage_InitFields();

void igRenderPackage_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderPackage_metaObject_00561450, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRenderPackage_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igRenderPackage_className_004e19e0,  /* class name */
        0x20,                                  /* instance size */
        igRenderPackage_GetVTable,             /* vtable getter */
        &igRenderPackage_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igRenderPackage_callbackList_0048b4c0  /* callback list */
    );
}
