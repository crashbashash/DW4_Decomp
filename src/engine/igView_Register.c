/* 0x0044bbc0 igView_Register: registers class igView with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igView_GetMetaObject[];
extern char g_igView_callbackList[];
extern char igView_className[];
extern char g_igView_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igView_InitFields();

void igView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igView_metaObject,          /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igView_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igView_className,           /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igView_InitFields,                    /* field adder */
        0,                                     /* extra callback item */
        g_igView_callbackList         /* callback list */
    );
}
