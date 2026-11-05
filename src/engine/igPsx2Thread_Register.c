/* 0x002cf550 igPsx2Thread_Register: registers class igPsx2Thread with the object system, derived from igThread.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igThread_Register[];
extern char thunk_igPsx2Thread_GetMetaObject[];
extern char igPsx2Thread_GetVTable[];
extern char igThread_GetPublishedMetaObject_002cf5d0[];
extern char g_igPsx2Thread_callbackList_004c1c70[];
extern char s_igPsx2Thread_className_004f8e58[];
extern char g_igPsx2Thread_metaObject_00586ca0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Thread_InitFields();

void igPsx2Thread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Thread_metaObject_00586ca0,       /* published MetaObject slot */
        igThread_Register,                        /* base class registrar */
        igThread_GetPublishedMetaObject_002cf5d0, /* base class MetaObject accessor */
        thunk_igPsx2Thread_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2Thread_className_004f8e58,        /* class name */
        0x40,                                     /* instance size */
        igPsx2Thread_GetVTable,                   /* vtable getter */
        &igPsx2Thread_InitFields,                 /* field adder */
        0,                                        /* extra callback item */
        g_igPsx2Thread_callbackList_004c1c70      /* callback list */
    );
}
