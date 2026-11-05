/* 0x0019e8a0 igProbe_Register: registers class igProbe with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igProbe_GetVTable[];
extern char thunk_igProbe_GetMetaObject[];
extern char igObject_Register[];
extern char g_igProbe_callbackList_0048be80[];
extern char s_igProbe_className_004e2558[];
extern char g_igProbe_metaObject_00561970[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igProbe_InitFields();

void igProbe_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProbe_metaObject_00561970,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igProbe_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igProbe_className_004e2558,          /* class name */
        0x14,                                  /* instance size */
        igProbe_GetVTable,                     /* vtable getter */
        &igProbe_InitFields,                   /* field adder */
        0,                                     /* extra callback item */
        g_igProbe_callbackList_0048be80        /* callback list */
    );
}
