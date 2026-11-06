/* 0x0019f7b0 igGraphPath_Register: registers class igGraphPath with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igGraphPath_GetVTable[];
extern char thunk_igGraphPath_GetMetaObject[];
extern char igObject_Register[];
extern char g_igGraphPath_callbackList[];
extern char igGraphPath_className[];
extern char g_igGraphPath_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igGraphPath_InitFields();

void igGraphPath_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGraphPath_metaObject,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igGraphPath_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igGraphPath_className,      /* class name */
        0x1C,                                  /* instance size */
        igGraphPath_GetVTable,                 /* vtable getter */
        &igGraphPath_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        g_igGraphPath_callbackList    /* callback list */
    );
}
