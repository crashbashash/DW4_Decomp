/* 0x001471c0 igPsx2Controller_Register: registers class igPsx2Controller with the object system, derived from igController.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igController_Register[];
extern char thunk_igPsx2Controller_GetMetaObject[];
extern char igPsx2Controller_GetVTable[];
extern char igController_GetPublishedMetaObject[];
extern char g_igPsx2Controller_callbackList[];
extern char igPsx2Controller_className[];
extern char g_igPsx2Controller_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2Controller_InitFields();

void igPsx2Controller_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Controller_metaObject,       /* published MetaObject slot */
        igController_Register,                        /* base class registrar */
        igController_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Controller_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2Controller_className,        /* class name */
        0x70,                                         /* instance size */
        igPsx2Controller_GetVTable,                   /* vtable getter */
        &igPsx2Controller_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPsx2Controller_callbackList      /* callback list */
    );
}
