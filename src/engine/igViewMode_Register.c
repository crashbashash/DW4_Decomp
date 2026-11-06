/* 0x0045d010 igViewMode_Register: registers class igViewMode with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igViewMode_GetVTable[];
extern char thunk_igViewMode_GetMetaObject[];
extern char igViewMode_className[];
extern char g_igViewMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewMode_InitFields();

void igViewMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewMode_metaObject,       /* published MetaObject slot */
        igView_Register,                        /* base class registrar */
        igView_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igViewMode_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igViewMode_className,        /* class name */
        0x4C,                                   /* instance size */
        igViewMode_GetVTable,                   /* vtable getter */
        &igViewMode_InitFields,                 /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
