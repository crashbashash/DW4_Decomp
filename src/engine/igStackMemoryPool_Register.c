/* 0x002ce060 igStackMemoryPool_Register: registers class igStackMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject_002cd480[];
extern char igStackMemoryPool_GetVTable[];
extern char thunk_igStackMemoryPool_GetMetaObject[];
extern char g_igStackMemoryPool_callbackList_004c1948[];
extern char s_igStackMemoryPool_className_004f8c30[];
extern char g_igStackMemoryPool_metaObject_00586b20[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStackMemoryPool_InitFields();

void igStackMemoryPool_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStackMemoryPool_metaObject_00586b20,      /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject_002cd480, /* base class MetaObject accessor */
        thunk_igStackMemoryPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igStackMemoryPool_className_004f8c30,       /* class name */
        0x98,                                         /* instance size */
        igStackMemoryPool_GetVTable,                  /* vtable getter */
        &igStackMemoryPool_InitFields,                /* field adder */
        0,                                            /* extra callback item */
        g_igStackMemoryPool_callbackList_004c1948     /* callback list */
    );
}
