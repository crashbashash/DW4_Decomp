/* 0x00450660 igGeometryElement_Register: registers class igGeometryElement with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igGeometryElement_GetMetaObject[];
extern char g_igGeometryElement_callbackList[];
extern char igGeometryElement_className[];
extern char g_igGeometryElement_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGeometryElement_InitFields();

void igGeometryElement_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryElement_metaObject, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igGeometryElement_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGeometryElement_className,  /* class name */
        0x2C,                                    /* instance size */
        0,                                       /* vtable getter */
        &igGeometryElement_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igGeometryElement_callbackList  /* callback list */
    );
}
