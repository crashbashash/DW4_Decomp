/* 0x002cf550 igPsx2Thread_Register: registers class igPsx2Thread with the object system, derived from igThread.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igThread_Register[];
extern char thunk_igPsx2Thread_GetMetaObject[];
extern char igPsx2Thread_GetVTable[];
extern char igThread_GetPublishedMetaObject[];
extern char g_igPsx2Thread_callbackList[];
extern char igPsx2Thread_className[];
extern char g_igPsx2Thread_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Thread_InitFields();

void igPsx2Thread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Thread_metaObject,       /* published MetaObject slot */
        igThread_Register,                        /* base class registrar */
        igThread_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Thread_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2Thread_className,        /* class name */
        0x40,                                     /* instance size */
        igPsx2Thread_GetVTable,                   /* vtable getter */
        &igPsx2Thread_InitFields,                 /* field adder */
        0,                                        /* extra callback item */
        g_igPsx2Thread_callbackList      /* callback list */
    );
}
