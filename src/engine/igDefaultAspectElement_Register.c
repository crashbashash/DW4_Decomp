/* 0x00451cb0 igDefaultAspectElement_Register: registers class igDefaultAspectElement with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igDefaultAspectElement_GetVTable[];
extern char thunk_igDefaultAspectElement_GetMetaObject[];
extern char g_igDefaultAspectElement_callbackList[];
extern char igDefaultAspectElement_className[];
extern char g_igDefaultAspectElement_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igDefaultAspectElement_InitFields();

void igDefaultAspectElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultAspectElement_metaObject, /* published MetaObject slot */
        igObject_Register,                            /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,        /* base class MetaObject accessor */
        thunk_igDefaultAspectElement_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDefaultAspectElement_className,  /* class name */
        0x20,                                         /* instance size */
        igDefaultAspectElement_GetVTable,             /* vtable getter */
        &igDefaultAspectElement_InitFields,           /* field adder */
        0,                                            /* extra callback item */
        g_igDefaultAspectElement_callbackList  /* callback list */
    );
}
