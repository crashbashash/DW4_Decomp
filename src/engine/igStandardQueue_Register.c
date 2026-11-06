/* 0x002cf0f0 igStandardQueue_Register: registers class igStandardQueue with the object system, derived from igQueue.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igQueue_Register[];
extern char thunk_igStandardQueue_GetMetaObject[];
extern char igStandardQueue_GetVTable[];
extern char igQueue_GetPublishedMetaObject[];
extern char g_igStandardQueue_callbackList[];
extern char igStandardQueue_className[];
extern char g_igStandardQueue_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStandardQueue_InitFields();

void igStandardQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStandardQueue_metaObject,   /* published MetaObject slot */
        igQueue_Register,                        /* base class registrar */
        igQueue_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStandardQueue_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igStandardQueue_className,    /* class name */
        0x2C,                                    /* instance size */
        igStandardQueue_GetVTable,               /* vtable getter */
        &igStandardQueue_InitFields,             /* field adder */
        0,                                       /* extra callback item */
        g_igStandardQueue_callbackList  /* callback list */
    );
}
