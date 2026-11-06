/* 0x002cfad0 igPsx2Media_Register: registers class igPsx2Media with the object system, derived from igMedia.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMedia_Register[];
extern char thunk_igPsx2Media_GetMetaObject[];
extern char igPsx2Media_GetVTable[];
extern char igMedia_GetPublishedMetaObject[];
extern char g_igPsx2Media_callbackList[];
extern char igPsx2Media_className[];
extern char g_igPsx2Media_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Media_InitFields();

void igPsx2Media_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Media_metaObject,       /* published MetaObject slot */
        igMedia_Register,                        /* base class registrar */
        igMedia_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Media_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2Media_className,        /* class name */
        0x28,                                    /* instance size */
        igPsx2Media_GetVTable,                   /* vtable getter */
        &igPsx2Media_InitFields,                 /* field adder */
        0,                                       /* extra callback item */
        g_igPsx2Media_callbackList      /* callback list */
    );
}
