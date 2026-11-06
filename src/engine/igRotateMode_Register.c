/* 0x0045c690 igRotateMode_Register: registers class igRotateMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject[];
extern char igRotateMode_GetVTable[];
extern char thunk_igRotateMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char igRotateMode_className[];
extern char g_igRotateMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igRotateMode_InitFields();

void igRotateMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRotateMode_metaObject,         /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRotateMode_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igRotateMode_className,          /* class name */
        0x94,                                       /* instance size */
        igRotateMode_GetVTable,                     /* vtable getter */
        &igRotateMode_InitFields,                   /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
