/* 0x00231cc0 igMessageFilter_Register: registers class igMessageFilter with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessageFilter_GetVTable[];
extern char thunk_igMessageFilter_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMessageFilter_callbackList[];
extern char igMessageFilter_className[];
extern char g_igMessageFilter_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igMessageFilter_InitFields();

void igMessageFilter_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageFilter_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMessageFilter_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMessageFilter_className,  /* class name */
        0x10,                                  /* instance size */
        igMessageFilter_GetVTable,             /* vtable getter */
        &igMessageFilter_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igMessageFilter_callbackList  /* callback list */
    );
}
