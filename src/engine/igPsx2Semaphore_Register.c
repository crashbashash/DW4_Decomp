/* 0x002cf7b0 igPsx2Semaphore_Register: registers class igPsx2Semaphore with the object system, derived from igSemaphore.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igSemaphore_Register[];
extern char thunk_igPsx2Semaphore_GetMetaObject[];
extern char igPsx2Semaphore_GetVTable[];
extern char igSemaphore_GetPublishedMetaObject[];
extern char igPsx2Semaphore_className[];
extern char g_igPsx2Semaphore_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Semaphore_InitFields();

void igPsx2Semaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Semaphore_metaObject,       /* published MetaObject slot */
        igSemaphore_Register,                        /* base class registrar */
        igSemaphore_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Semaphore_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2Semaphore_className,        /* class name */
        0x18,                                        /* instance size */
        igPsx2Semaphore_GetVTable,                   /* vtable getter */
        &igPsx2Semaphore_InitFields,                 /* field adder */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
