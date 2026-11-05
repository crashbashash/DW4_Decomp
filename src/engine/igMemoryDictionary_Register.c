/* 0x002c11a0 igMemoryDictionary_Register: registers class igMemoryDictionary with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMemoryDictionary_GetVTable[];
extern char thunk_igMemoryDictionary_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMemoryDictionary_callbackList_004c0380[];
extern char s_igMemoryDictionary_className_004f6dd0[];
extern char g_igMemoryDictionary_metaObject_00585fa0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryDictionary_InitFields();

void igMemoryDictionary_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryDictionary_metaObject_00585fa0, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igMemoryDictionary_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryDictionary_className_004f6dd0,  /* class name */
        0x18,                                     /* instance size */
        igMemoryDictionary_GetVTable,             /* vtable getter */
        &igMemoryDictionary_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igMemoryDictionary_callbackList_004c0380  /* callback list */
    );
}
