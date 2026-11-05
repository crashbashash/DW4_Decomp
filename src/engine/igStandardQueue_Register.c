/* 0x002cf0f0 igStandardQueue_Register: registers class igStandardQueue with the object system, derived from igQueue.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igQueue_Register[];
extern char thunk_igStandardQueue_GetMetaObject[];
extern char igStandardQueue_GetVTable[];
extern char igQueue_GetPublishedMetaObject_002cf170[];
extern char g_igStandardQueue_callbackList_004c1be8[];
extern char s_igStandardQueue_className_004f8dc0[];
extern char g_igStandardQueue_metaObject_00586c50[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStandardQueue_InitFields();

void igStandardQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStandardQueue_metaObject_00586c50,   /* published MetaObject slot */
        igQueue_Register,                        /* base class registrar */
        igQueue_GetPublishedMetaObject_002cf170, /* base class MetaObject accessor */
        thunk_igStandardQueue_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igStandardQueue_className_004f8dc0,    /* class name */
        0x2C,                                    /* instance size */
        igStandardQueue_GetVTable,               /* vtable getter */
        &igStandardQueue_InitFields,             /* field adder */
        0,                                       /* extra callback item */
        g_igStandardQueue_callbackList_004c1be8  /* callback list */
    );
}
